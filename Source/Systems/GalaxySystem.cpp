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
    Engine& engine = Engine::instance();
    engine.keyboard().registerListener(*this);
}

void GalaxySystem::initialize()
{
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
            for (SpiralGalaxy& galaxy : scene().components<SpiralGalaxy>())
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

void GalaxySystem::onComponentAdded(SpiralGalaxy::Iterator galaxy)
{
    generateSpiralGalaxy(galaxy);
}

void GalaxySystem::receiveEvent(const KeyboardEvent& event)
{
    if (event.key == Key::F5 && event.type == KeyboardEventType::KeyDown)
    {
        for (SpiralGalaxy& galaxy : scene().components<SpiralGalaxy>())
        {
            Entity::Iterator entity = galaxy.entity();
            if (!entity->isPendingDestruction())
            {
                entity->destroy();
            }
        }

        Entity::Iterator entity = scene().createEntity();
        entity->addComponent<SpiralGalaxy>();
        entity->activate();
    }
    else if (event.key == Key::F6 && event.type == KeyboardEventType::KeyDown)
    {
        for (SpiralGalaxy& galaxy : scene().components<SpiralGalaxy>())
        {
            Entity::Iterator entity = galaxy.entity();
            Model::Iterator model = entity->component<Model>();
            ModelSurface& surface = model->surfaces[0];
            surface.visible = !surface.visible;
        }
    }
}

void GalaxySystem::generateSpiralGalaxy(SpiralGalaxy::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    // Create the random number generator for this galaxy
    if (galaxy->seed == 0)
    {
        galaxy->seed = static_cast<RandomSeed>(Timer::totalElapsed().milliseconds());
    }
    Random random(galaxy->seed);

    // Generate the numerical properties about the galaxy
    galaxy->diameter = random.next(spiralDiameterRange[0], spiralDiameterRange[1]);
    galaxy->thickness = random.next(spiralThicknessRange[0], spiralThicknessRange[1]);
    galaxy->density = static_cast<unsigned>(random.next(spiralDensityRange[0], spiralDensityRange[1]));

    // Compute minimum
    double horizontalRadius = galaxy->diameter / 2.0;
    double verticalRadius = galaxy->thickness / 2.0;
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
            Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, size, localPosition, Vector3::Zero);
            entity->addChild(*rootGalaxyNode);
        }
    }

    // Add the bounding box for the whole galaxy
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();

    // Add the model for the topology and particle layer meshes
    Model::Iterator model = entity->addComponent<Model>();

    createTopologyMesh(galaxy);
    createParticlesMesh(galaxy);
}

void GalaxySystem::createTopologyMesh(SpiralGalaxy::Iterator galaxy)
{
    // Create mesh
    Mesh::Handle mesh(new Mesh("Topology"));
    mesh->setPrimitiveType(PrimitiveType::Triangles);

    // Write the vertex/index data
    VertexAttributeSemantic position = VertexAttributeSemantic::Position;
    VertexAttributeSemantic textureCoords = VertexAttributeSemantic::TextureCoords0;
    MeshWriter meshWriter(*mesh);
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(-0.5, -0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(0.0, 0.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(0.5, -0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(1.0, 0.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(0.5, 0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(1.0, 1.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(-0.5, 0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(0.0, 1.0));
    meshWriter.addIndex(0);
    meshWriter.addIndex(1);
    meshWriter.addIndex(2);
    meshWriter.addIndex(2);
    meshWriter.addIndex(3);
    meshWriter.addIndex(0);

    // Generate the topology texture
    generateTopologyTexture(galaxy);

    // Create the material
    Material::Handle material(new Material("Topology"));
    material->setShader(topologyShader);
    material->setUniformValue("additiveTexture", galaxy->topologyTexture);
    material->setUniformValue("intensity", 0.12);
    material->setCullMode(CullMode::None);

    // Add the mesh to the galaxy's model
    Model::Iterator model = galaxy->entity()->component<Model>();
    model->addSurface(mesh, material);
}

void GalaxySystem::createParticlesMesh(SpiralGalaxy::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    VertexLayout vertexLayout;
    VertexAttribute position(VertexAttributeSemantic::Position, VertexAttributeType::Float32, 3);
    vertexLayout.addAttribute(position);
    VertexAttribute color(VertexAttributeSemantic::Color, VertexAttributeType::Float32, 3);
    vertexLayout.addAttribute(color);
    VertexAttribute size(VertexAttributeSemantic::Weight0, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(size);
    VertexAttribute rotation(VertexAttributeSemantic::Weight1, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(rotation);

    Mesh::Handle mesh(new Mesh("Particles"));
    mesh->setVertexLayout(vertexLayout);
    mesh->setPrimitiveType(PrimitiveType::Points);

    MeshWriter writer(*mesh);

    Random random(galaxy->seed);

    BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
    Vector3 halfSize = boundingBox->extents.size() / 2;
    halfSize.z = galaxy->thickness;

    unsigned particleCount = 0;
    while (particleCount < galaxy->density)
    {
        Vector3 position = random.next(-halfSize, halfSize);

        Color color;
        double thickness = 0.0;
        sampleTopology(galaxy, position, color, thickness);
        if (random.next(0.0, 1.0) < thickness)
        {
            position.z = random.next(-thickness, thickness) * galaxy->thickness * 0.5;
            double size = random.next(2000.0, 8000.0);
            double rotation = random.next(0.0, 2.0 * pi);

            writer.addVertex();
            writer.writeAttributeData(VertexAttributeSemantic::Position, position);
            writer.writeAttributeData(VertexAttributeSemantic::Color, Vector3(color.r, color.g, color.b));
            writer.writeAttributeData(VertexAttributeSemantic::Weight0, size);
            writer.writeAttributeData(VertexAttributeSemantic::Weight1, rotation);
            writer.addIndex(particleCount);

            ++particleCount;
        }
    }

    // Generate the particle texture
    Texture2::Handle texture = generateParticleTexture(galaxy);

    // Create the material
    Material::Handle material(new Material("Particle"));
    material->setShader(particleShader);
    material->setUniformValue("particleTexture", texture);
    material->setCullMode(CullMode::None);

    // Add the mesh to the galaxy's model
    Model::Iterator model = galaxy->entity()->component<Model>();
    model->addSurface(mesh, material);
}

Texture2::Handle GalaxySystem::generateParticleTexture(SpiralGalaxy::Iterator galaxy)
{
    Texture2::Handle texture(new Texture2("Particle", particleTextureResolution, particleTextureResolution, PixelFormat::Rgb8, TextureFilter::Linear, TextureFilter::Linear, false, false));

    FrameBuffer frameBuffer(particleTextureResolution, particleTextureResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer& renderer = Engine::instance().renderer();
    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *particleGenerateShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), Random(galaxy->seed).next(-10000.0, 10000.0));
    frame.renderViewport();

    return texture;
}

void GalaxySystem::generateTopologyTexture(SpiralGalaxy::Iterator galaxy)
{
    galaxy->topologyTexture = new Texture2("Topology", topologyTextureResolution, topologyTextureResolution, PixelFormat::Rgba32, TextureFilter::Linear, TextureFilter::Linear, false, false);

    FrameBuffer frameBuffer(topologyTextureResolution, topologyTextureResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *galaxy->topologyTexture);

    Renderer& renderer = Engine::instance().renderer();
    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *spiralGenerateTopologyShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), Random(galaxy->seed).next(-10000.0, 10000.0));

    frame.renderViewport();
}

void GalaxySystem::sampleTopology(SpiralGalaxy::Iterator galaxy, const Vector3& position, Color& color, double& thickness)
{
    Vector3 coords;

    BoundingBox::Iterator boundingBox = galaxy->entity()->component<BoundingBox>();

    AxisAlignedBox& extents = boundingBox->extents;
    Vector3 totalSize = extents.size();
    coords = (position - extents.minimum()) / totalSize;

    Vector2 densityCoords(coords.x, coords.y);
    color = galaxy->topologyTexture->readPixel(densityCoords);
    thickness = color.a;
    color.a = 1.0;
}

Entity::Iterator GalaxySystem::createGalaxyNode(SpiralGalaxy::Iterator galaxy, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition)
{
    // Create the galaxy node entity
    Entity::Iterator entity = scene().createEntity();
    entity->setTransient(true);

    // Add transform component
    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->localPosition = localPosition;
    transform->globalPosition = parentGlobalPosition + localPosition;

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
            SpiralGalaxy::Iterator galaxy = galaxyNode->galaxy;

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
    if (galaxyNode && !galaxyNode->split && galaxyNode->radius > 600.0)
    {
        Entity::Iterator parent = entity->iterator();

        // Get the bounding box component
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (boundingBox)
        {
            SpiralGalaxy::Iterator galaxy = galaxyNode->galaxy;

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
                        Entity::Iterator child = createGalaxyNode(galaxy, size, localPosition, parentGlobalPosition);
                        parent->addChild(*child);
                    }
                }
            }

            galaxyNode->split = true;
        }
    }
}
