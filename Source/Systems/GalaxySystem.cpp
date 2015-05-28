///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxySystem.h"

using namespace zeroth;

GalaxySystem::GalaxySystem(Scene& scene) :
    System(scene),
    _cameraSystem(scene.system<CameraSystem>())
{
    createDensityPointsMesh();
}

void GalaxySystem::tick(double timeStep)
{
    (void)timeStep;

    if (_cameraSystem)
    {
        // If there is an active camera
        Camera::Iterator activeCamera = _cameraSystem->activeCamera();
        if (activeCamera)
        {
            Vector3 cameraPosition = activeCamera->position;

            // For each galaxy
            for (Galaxy& galaxy : scene().components<Galaxy>())
            {
                // Adapt each root galaxy node to the camera position
                Entity::Iterator galaxyEntity = galaxy.entity();
                for (Entity& child : galaxyEntity->children())
                {
                    Entity::Iterator rootGalaxyNode = child.iterator();
                    adaptGalaxyNode(cameraPosition, rootGalaxyNode);
                }
            }
        }
    }
}

void GalaxySystem::onComponentAdded(Galaxy::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    // Compute minimum
    double horizontalRadius = galaxy->horizontalRadius;
    double verticalRadius = galaxy->verticalRadius;
    const Vector3 minimum(-horizontalRadius, -horizontalRadius, -verticalRadius);

    // Compute the ratio of horizontal to vertical nodes
    double ratio = horizontalRadius / verticalRadius;
    int rootNodeCount = static_cast<int>(ratio);

    // The size of each root node
    Vector3 size(horizontalRadius * 2.0 / rootNodeCount);
    size.z = verticalRadius * 2.0;
    Vector3 halfSize = size / 2.0;

    // Create the root nodes of the galaxy
    for (int x = 0; x < rootNodeCount; ++x)
    {
        for (int y = 0; y < rootNodeCount; ++y)
        {
            Vector3 localPosition = minimum + size * Vector3(x, y, 0) + halfSize;
            Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, 0, size, localPosition, Vector3::Zero);
            galaxy->entity()->addChild(*rootGalaxyNode);
        }
    }

    // Add the bounding box for the whole galaxy
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();

    // Add the model for the particle meshes
    Model::Iterator model = entity->addComponent<Model>();

    // Generate star layers
    for (StarLayer& layer : galaxy->starLayers)
    {
        generateStarLayer(layer, galaxy, boundingBox, model);
    }
}

Entity::Iterator GalaxySystem::createGalaxyNode(Galaxy::Iterator galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition)
{
    // Create the galaxy node entity
    Entity::Iterator entity = scene().createEntity();
    entity->setTransient(true);

    // Add transform component
    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->localPosition = localPosition;

    // Add bounding box component
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();
    boundingBox->adaptive = false;
    Vector3 minimum = parentGlobalPosition + localPosition;
    Vector3 halfSize = size / 2;
    boundingBox->extents = AxisAlignedBox(minimum - size / 2, minimum + size / 2);

    // Add galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->addComponent<GalaxyNode>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = size.length() / 2;
    galaxyNode->level = level;

    // Activate and return the entity
    entity->activate();
    return entity;
}

void GalaxySystem::adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode)
    {
        Transform::Iterator transform = entity->component<Transform>();
        if (transform)
        {
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            double distance = (cameraPosition - transform->globalPosition).length();
            if (galaxyNode->split && distance > galaxyNode->radius * 2.0)
            {
                joinGalaxyNode(entity);
            }
            else if (!galaxyNode->split && distance < galaxyNode->radius * 1.9)
            {
                splitGalaxyNode(entity);
            }
            else
            {
                for (Entity& child : entity->children())
                {
                    adaptGalaxyNode(cameraPosition, child.iterator());
                }
            }
        }
    }
}

void GalaxySystem::joinGalaxyNode(Entity::Iterator entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && galaxyNode->split)
    {
        entity->destroyAllChildren();
        galaxyNode->split = false;
    }
}

void GalaxySystem::splitGalaxyNode(Entity::Iterator entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && !galaxyNode->split && galaxyNode->level < galaxyNode->galaxy->maxLevel)
    {
        Entity::Iterator parent = entity->iterator();
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (galaxyNode && boundingBox && !galaxyNode->split)
        {
            unsigned level = galaxyNode->level + 1;
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            Vector3 size = boundingBox->extents.size() / 2;
            Vector3 halfSize = size / 2;
            Vector3 parentGlobalPosition = boundingBox->extents.center();

            // Create the child nodes
            std::vector<int> values { -1, 1 };
            for (int x : values)
            {
                for (int y : values)
                {
                    for (int z : values)
                    {
                        const Vector3 localPosition = halfSize * Vector3(x, y, z);
                        Entity::Iterator child = createGalaxyNode(galaxy, level, size, localPosition, parentGlobalPosition);
                        parent->addChild(*child);
                    }
                }
            }

            galaxyNode->split = true;
        }
    }
}

void GalaxySystem::initializeStarLayer(StarLayer& layer, Galaxy::Iterator galaxy)
{
    renderDensityTexture(layer);
    renderParticleTexture(galaxy->seed, layer);

    // Create the particle material
    layer.particleMaterial = Material::Handle(new Material());
    layer.particleMaterial->setShader(particleShader);
    layer.particleMaterial->setUniformValue("particleTexture", layer.particleTexture);
    layer.particleMaterial->setCullMode(CullMode::None);
}

void GalaxySystem::generateStarLayer(StarLayer& layer, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model)
{
    initializeStarLayer(layer, galaxy);

    VertexLayout vertexLayout;
    VertexAttribute position(VertexAttributeSemantic::Position, VertexAttributeType::Float32, 3);
    vertexLayout.addAttribute(position);
    VertexAttribute size(VertexAttributeSemantic::Weight0, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(size);
    VertexAttribute rotation(VertexAttributeSemantic::Weight1, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(rotation);
    VertexAttribute brightness(VertexAttributeSemantic::Weight2, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(brightness);

    Mesh::Handle mesh(new Mesh(layer.name));
    mesh->setVertexLayout(vertexLayout);
    mesh->setPrimitiveType(PrimitiveType::Points);

    MeshWriter writer(*mesh);

    Random random(galaxy->seed);

    Vector3 halfSize = boundingBox->extents.size() / 2;

    unsigned particleCount = 0;
    while (particleCount < layer.density)
    {
        Vector3 position = random.next(-halfSize, halfSize);
        double densityValue = computeDensity(layer, boundingBox, position);

        if (random.next(0.0, 1.0) < densityValue)
        {
            double size = random.next(layer.sizeRange.x, layer.sizeRange.y);
            double rotation = random.next(0.0, 2.0 * pi);
            double brightness = layer.brightnessRange.x + (layer.brightnessRange.y - layer.brightnessRange.x) * densityValue;

            writer.addVertex();
            writer.writeAttributeData(VertexAttributeSemantic::Position, position);
            writer.writeAttributeData(VertexAttributeSemantic::Weight0, size);
            writer.writeAttributeData(VertexAttributeSemantic::Weight1, rotation);
            writer.writeAttributeData(VertexAttributeSemantic::Weight2, brightness);
            writer.addIndex(particleCount);

            ++particleCount;
        }
    }

    model->surfaces.push_back(ModelSurface(mesh, layer.particleMaterial));
}

double GalaxySystem::computeDensity(StarLayer& layer, BoundingBox::Iterator boundingBox, const Vector3& position)
{
    AxisAlignedBox& extents = boundingBox->extents;
    Vector3 totalSize = extents.size();
    Vector3 coords = (position - extents.minimum()) / totalSize;

    return layer.densityTexture->readPixel(coords).r;
}

void GalaxySystem::renderDensityTexture(StarLayer& layer)
{
    Texture3::Handle texture(new Texture3(layer.name + ".Density", densityResolution, densityResolution, densityResolution, PixelFormat::Rgb32, TextureFilter::Linear, TextureFilter::Linear, false, false));

    FrameBuffer frameBuffer(densityResolution, densityResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer& renderer = Engine::instance().renderer();

    Renderer::Frame frame = renderer.beginFrame(frameBuffer);
    frame.setShader(*layer.proceduralDensityShader);
    frame.renderMesh(_densityPointsMesh);

    layer.densityTexture = texture;
}

void GalaxySystem::renderParticleTexture(RandomSeed seed, StarLayer& layer)
{
    Texture2::Handle texture(new Texture2(layer.name + ".Particle", particleResolution, particleResolution, PixelFormat::Rgba8, TextureFilter::Linear, TextureFilter::Linear, false, false));
    
    FrameBuffer frameBuffer(particleResolution, particleResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer& renderer = Engine::instance().renderer();

    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *layer.proceduralParticleShader;
    frame.setShader(shader);
    if (shader.hasUniform("seed"))
    {
        Random random(seed);
        double seed = random.next(-10000.0, 10000.0);
        frame.setUniform(shader.uniform("seed"), seed);
    }

    frame.renderViewport();

    layer.particleTexture = texture;
}

void GalaxySystem::createDensityPointsMesh()
{
    _densityPointsMesh = Mesh("DensityPoints");

    VertexLayout vertexLayout;
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float32, 3));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight0, VertexAttributeType::Int32, 1));
    _densityPointsMesh.setVertexLayout(vertexLayout);

    _densityPointsMesh.setPrimitiveType(PrimitiveType::Points);

    Vector3 dimensions(densityResolution, densityResolution, densityResolution);
    dimensions -= Vector3::One;

    MeshWriter meshWriter(_densityPointsMesh);
    for (unsigned z = 0; z < densityResolution; ++z)
    {
        for (unsigned y = 0; y < densityResolution; ++y)
        {
            for (unsigned x = 0; x < densityResolution; ++x)
            {
                Vector3 position(x, y, z);
                position /= dimensions;
                position -= 0.5;
                position *= 1.95;

                size_t index = meshWriter.addVertex();
                meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
                meshWriter.writeAttributeData(VertexAttributeSemantic::Weight0, z);
                meshWriter.addIndex(index);
            }
        }
    }
}
