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
}

void GalaxySystem::initialize()
{
    _densityPointsMesh = createDensityPointsMesh();
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

    // Initialize star layers
    for (StarLayer& starLayer : galaxy->starLayers)
    {
        initializeStarLayer(starLayer, galaxy, boundingBox, model);
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
    // Get the galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode)
    {
        // Get the transform component
        Transform::Iterator transform = entity->component<Transform>();
        if (transform)
        {
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            // Compute the distance from the camera to the node
            double distance = (cameraPosition - transform->globalPosition).length();

            // If the node is split and it is far enough away to join
            if (galaxyNode->split && distance > galaxyNode->radius * 2.0)
            {
                joinGalaxyNode(entity);
            }

            // If the node is not split and is close enough to split
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
    // If the node is not split and is not at the maximum level
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && !galaxyNode->split && galaxyNode->level < galaxyNode->galaxy->maxLevel)
    {
        Entity::Iterator parent = entity->iterator();

        // Get the bounding box component
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (boundingBox)
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

void GalaxySystem::initializeStarLayer(StarLayer& starLayer, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model)
{
    renderDensityTexture(starLayer);

    for (ParticleLayer& particleLayer : starLayer.particleLayers)
    {
        renderParticleTexture(galaxy->seed, particleLayer);
        generateParticleLayer(starLayer, particleLayer, galaxy, boundingBox, model);
    }
}

void GalaxySystem::generateParticleLayer(StarLayer& starLayer, ParticleLayer& particleLayer, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model)
{
    Random random(galaxy->seed);
    Vector3 halfSize = boundingBox->extents.size() / 2;

    VertexAttributeType attributeType = VertexAttributeType::Float32;
    VertexLayout vertexLayout;
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Position, attributeType, 3));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight0, attributeType, 1));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight1, attributeType, 1));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight2, attributeType, 1));

    // Create the mesh containing the points for the particles
    Mesh::Handle mesh(new Mesh(particleLayer.name));
    mesh->setVertexLayout(vertexLayout);
    mesh->setPrimitiveType(PrimitiveType::Points);
    MeshWriter writer(*mesh);

    // Generate particles until we meet the density of this layer
    unsigned particleCount = 0;
    while (particleCount < particleLayer.density)
    {
        // Pick a random point and check if it could be particle location
        Vector3 position = random.next(-halfSize, halfSize);
        double densityValue = computeDensity(starLayer, boundingBox, position);
        if (random.next(0.0, 1.0) < densityValue)
        {
            double size = random.next(particleLayer.sizeRange.x, particleLayer.sizeRange.y);
            double rotation = random.next(0.0, 2.0 * pi);
            double brightness = particleLayer.brightnessRange.x + (particleLayer.brightnessRange.y - particleLayer.brightnessRange.x) * densityValue;

            writer.addVertex();
            writer.writeAttributeData(VertexAttributeSemantic::Position, position);
            writer.writeAttributeData(VertexAttributeSemantic::Weight0, size);
            writer.writeAttributeData(VertexAttributeSemantic::Weight1, rotation);
            writer.writeAttributeData(VertexAttributeSemantic::Weight2, brightness);
            writer.addIndex(particleCount);

            ++particleCount;
        }
    }

    model->surfaces.push_back(ModelSurface(mesh, particleLayer.particleMaterial));
}

void GalaxySystem::renderDensityTexture(StarLayer& starLayer)
{
    Texture3::Handle texture(new Texture3(starLayer.name + ".Density", densityResolution, densityResolution, densityResolution, PixelFormat::Rg32, TextureFilter::Linear, TextureFilter::Linear, false, false));

    FrameBuffer frameBuffer(densityResolution, densityResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer& renderer = Engine::instance().renderer();

    Renderer::Frame frame = renderer.beginFrame(frameBuffer);
    frame.setShader(*starLayer.densityShader);
    frame.renderMesh(_densityPointsMesh);

    starLayer.densityTexture = texture;
}

void GalaxySystem::renderParticleTexture(RandomSeed seed, ParticleLayer& particleLayer)
{
    Texture2::Handle texture(new Texture2(particleLayer.name + ".Particle", particleResolution, particleResolution, PixelFormat::Rgba8, TextureFilter::Linear, TextureFilter::Linear, false, false));

    FrameBuffer frameBuffer(particleResolution, particleResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer& renderer = Engine::instance().renderer();

    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *particleLayer.particleShader;
    frame.setShader(shader);
    if (shader.hasUniform("seed"))
    {
        Random random(seed);
        double seed = random.next(-10000.0, 10000.0);
        frame.setUniform(shader.uniform("seed"), seed);
    }

    frame.renderViewport();

    particleLayer.particleTexture = texture;
    particleLayer.particleMaterial = Material::Handle(new Material());
    particleLayer.particleMaterial->setShader(particleShader);
    particleLayer.particleMaterial->setUniformValue("particleTexture", texture);
    particleLayer.particleMaterial->setCullMode(CullMode::None);
}

double GalaxySystem::computeDensity(StarLayer& starLayer, BoundingBox::Iterator boundingBox, const Vector3& position)
{
    AxisAlignedBox& extents = boundingBox->extents;
    Vector3 totalSize = extents.size();
    Vector3 coords = (position - extents.minimum()) / totalSize;

    return starLayer.densityTexture->readPixel(coords).r;
}

Mesh GalaxySystem::createDensityPointsMesh() const
{
    Mesh mesh("DensityPoints");

    VertexLayout vertexLayout;
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float32, 3));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight0, VertexAttributeType::Int32, 1));
    mesh.setVertexLayout(vertexLayout);

    mesh.setPrimitiveType(PrimitiveType::Points);

    Vector3 dimensions(densityResolution, densityResolution, densityResolution);
    dimensions -= 1;

    MeshWriter meshWriter(mesh);
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

    return mesh;
}
