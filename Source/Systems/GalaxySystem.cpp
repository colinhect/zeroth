///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxySystem.h"

using namespace zeroth;

GalaxySystem::GalaxySystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void GalaxySystem::adaptGalaxyNodes()
{
    // If there is an active camera
    auto& cameraSystem = scene().system<CameraSystem>();
    CameraComponent::Iterator activeCamera = cameraSystem.activeCamera();
    if (activeCamera)
    {
        Vector3 cameraPosition = activeCamera->position;

        // For each galaxy
        for (SpiralGalaxyComponent& galaxy : scene().components<SpiralGalaxyComponent>())
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

void GalaxySystem::generateSpiralGalaxy(SpiralGalaxyComponent::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    // If no seed was specified then generate a random seed
    if (galaxy->seed == 0)
    {
        galaxy->seed = Random().next();
    }

    // Generate the numerical properties about the galaxy
    Random random(galaxy->seed);
    galaxy->diameter = random.next(spiralDiameterRange[0], spiralDiameterRange[1]);
    galaxy->thickness = random.next(spiralThicknessRange[0], spiralThicknessRange[1]);
    galaxy->density = static_cast<unsigned>(galaxy->diameter * 0.011);

    HECT_DEBUG(format("Seed: %i", galaxy->seed));

    // Compute radii and minimum
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
            Entity::Iterator rootNode = createGalaxyNode(galaxy, size, localPosition, Vector3::Zero, true);
            entity->addChild(*rootNode);
        }
    }

    // Add the bounding box for the galaxy
    BoundingBoxComponent::Iterator boundingBox = entity->addComponent<BoundingBoxComponent>();

    // Add the mesh for the topology and particle meshes
    MeshComponent::Iterator mesh = entity->addComponent<MeshComponent>();
    createTopologyMesh(galaxy);
    createParticlesMesh(galaxy);
}

void GalaxySystem::createTopologyMesh(SpiralGalaxyComponent::Iterator galaxy)
{
    // Create the mesh
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
    material->setUniformValue("topologyTexture", galaxy->topologyTexture);
    material->setCullMode(CullMode::None);

    // Add the mesh to the galaxy's mesh
    MeshComponent::Iterator meshComponent = galaxy->entity()->component<MeshComponent>();
    meshComponent->addSurface(mesh, material);
}

void GalaxySystem::createParticlesMesh(SpiralGalaxyComponent::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    // Create the vertex layout
    VertexLayout vertexLayout;
    VertexAttribute position(VertexAttributeSemantic::Position, VertexAttributeType::Float32, 3);
    vertexLayout.addAttribute(position);
    VertexAttribute color(VertexAttributeSemantic::Color, VertexAttributeType::Float32, 3);
    vertexLayout.addAttribute(color);
    VertexAttribute size(VertexAttributeSemantic::Weight0, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(size);
    VertexAttribute rotation(VertexAttributeSemantic::Weight1, VertexAttributeType::Float32, 1);
    vertexLayout.addAttribute(rotation);

    // Create the mesh
    Mesh::Handle particlesMesh(new Mesh("Particles"));
    particlesMesh->setVertexLayout(vertexLayout);
    particlesMesh->setPrimitiveType(PrimitiveType::Points);
    MeshWriter writer(*particlesMesh);

    // Compute the half-size of the galaxy
    BoundingBoxComponent::Iterator boundingBox = entity->component<BoundingBoxComponent>();
    Vector3 halfSize = boundingBox->extents.size() / 2;

    // Add particle until the density is satisfied
    Random random(galaxy->seed);
    unsigned particleCount = 0;
    while (particleCount < galaxy->density)
    {
        // Pick a point in the galaxy
        Vector3 position = random.next(-halfSize, halfSize);
        position.z = 0.0;

        // Sample the color/density for the point
        Color color;
        double thickness = 0.0;
        sampleTopology(galaxy, boundingBox, position, color, thickness);

        // If the point resulted in a particle
        if (random.next(0.0, 1.0) < thickness)
        {
            // Generate the size/rotation of the particle
            double size = lerp(spiralParticleSizeRange[0], spiralParticleSizeRange[1], random.next(0.0, thickness));
            double rotation = random.next(0.0, 2.0 * Pi);

            // Add the particle's vertex in the mesh
            writer.addVertex();
            writer.writeAttributeData(VertexAttributeSemantic::Position, position);
            writer.writeAttributeData(VertexAttributeSemantic::Color, color);
            writer.writeAttributeData(VertexAttributeSemantic::Weight0, size);
            writer.writeAttributeData(VertexAttributeSemantic::Weight1, rotation);
            writer.addIndex(particleCount);

            ++particleCount;
        }
    }

    // Generate the particle texture
    generateParticleTexture(galaxy);

    // Create the material
    Material::Handle material(new Material("Particle"));
    material->setShader(particleShader);
    material->setUniformValue("particleTexture", galaxy->particleTexture);
    material->setCullMode(CullMode::None);

    // Add the mesh to the galaxy's mesh
    MeshComponent::Iterator mesh = galaxy->entity()->component<MeshComponent>();
    mesh->addSurface(particlesMesh, material);
}

void GalaxySystem::generateTopologyTexture(SpiralGalaxyComponent::Iterator galaxy)
{
    galaxy->topologyTexture = new Texture2("Topology", topologyTextureResolution, topologyTextureResolution, PixelFormat::Rgba32, TextureFilter::Linear, TextureFilter::Linear, false, false);

    FrameBuffer frameBuffer(topologyTextureResolution, topologyTextureResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *galaxy->topologyTexture);

    Renderer& renderer = engine().renderer();
    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *generateTopologyShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), createSeedUniformValue(galaxy->seed));

    frame.renderViewport();
}

void GalaxySystem::generateParticleTexture(SpiralGalaxyComponent::Iterator galaxy)
{
    galaxy->particleTexture = new Texture2("Particle", particleTextureResolution, particleTextureResolution, PixelFormat::Rg8, TextureFilter::Linear, TextureFilter::Linear, false, false);

    FrameBuffer frameBuffer(particleTextureResolution, particleTextureResolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *galaxy->particleTexture);

    Renderer& renderer = engine().renderer();
    Renderer::Frame frame = renderer.beginFrame(frameBuffer);

    Shader& shader = *generateParticleShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), createSeedUniformValue(galaxy->seed));
    frame.renderViewport();
}

void GalaxySystem::sampleTopology(SpiralGalaxyComponent::Iterator galaxy, BoundingBoxComponent::Iterator boundingBox, Vector3 position, Color& color, double& thickness)
{
    AxisAlignedBox& extents = boundingBox->extents;
    Vector3 totalSize = extents.size();
    Vector3 coords = (position - extents.minimum()) / totalSize;

    Vector2 densityCoords(coords.x, coords.y);
    color = galaxy->topologyTexture->readPixel(densityCoords);
    thickness = color.a;
    color.a = 1.0;
}

void GalaxySystem::generateStars(GalaxyNodeComponent::Iterator galaxyNode, SpiralGalaxyComponent::Iterator galaxy, BoundingBoxComponent::Iterator boundingBox, MeshComponent::Iterator mesh)
{
    Vector3 globalPosition = boundingBox->extents.center();
    Random random(galaxy->seed + static_cast<RandomSeed>(globalPosition.x * globalPosition.y * globalPosition.z * galaxy->seed));
    Vector3 halfSize = boundingBox->extents.size() / 2;
    double verticalRadius = galaxy->thickness / 2.0;
    double verticalFalloff = 1.0 - (std::abs(globalPosition.z) / verticalRadius);

    VertexAttributeType attributeType = VertexAttributeType::Float32;
    VertexLayout vertexLayout;
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Position, attributeType, 3));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight0, attributeType, 1));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight1, attributeType, 1));
    vertexLayout.addAttribute(VertexAttribute(VertexAttributeSemantic::Weight2, attributeType, 1));

    // Create the mesh containing the points for the stars
    Mesh::Handle starsMesh(new Mesh("Stars"));
    starsMesh->setVertexLayout(vertexLayout);
    starsMesh->setPrimitiveType(PrimitiveType::PointSprites);
    MeshWriter writer(*starsMesh);

    BoundingBoxComponent::Iterator galaxyBoundingBox = galaxy->entity()->component<BoundingBoxComponent>();

    // Sample the color/density for the node
    Color color;
    double thickness = 0.0;
    sampleTopology(galaxy, galaxyBoundingBox, globalPosition, color, thickness);

    // Generate stars
    for (unsigned i = 0; i < maxStarsPerNode * thickness * verticalFalloff; ++i)
    {
        Vector3 position = random.next(-halfSize, halfSize);
        double size = random.next(0.0, 1.0);
        double brightness = random.next(0.0, 1.0);

        size_t vertexIndex = writer.addVertex();
        writer.writeAttributeData(VertexAttributeSemantic::Position, position);
        writer.writeAttributeData(VertexAttributeSemantic::Weight0, size);
        writer.writeAttributeData(VertexAttributeSemantic::Weight1, brightness);
        writer.writeAttributeData(VertexAttributeSemantic::Weight2, galaxyNode->radius * 2.0);
        writer.addIndex(vertexIndex);
    }

    mesh->surfaces.push_back(MeshSurface(starsMesh, starMaterial));
}

Entity::Iterator GalaxySystem::createGalaxyNode(SpiralGalaxyComponent::Iterator galaxy, Vector3 size, Vector3 localPosition, Vector3 parentGlobalPosition, bool rootNode)
{
    // Create the galaxy node entity
    Entity::Iterator entity = scene().createEntity("GalaxyNodeComponent");
    entity->setTransient(true);

    // Add transform component
    TransformComponent::Iterator transform = entity->addComponent<TransformComponent>();
    transform->mobility = Mobility::Static;
    transform->localPosition = localPosition;
    transform->globalPosition = parentGlobalPosition + localPosition;

    // Add bounding box component
    BoundingBoxComponent::Iterator boundingBox = entity->addComponent<BoundingBoxComponent>();
    boundingBox->adaptive = false;
    Vector3 minimum = parentGlobalPosition + localPosition;
    //Vector3 halfSize = size / 2;
    boundingBox->extents = AxisAlignedBox(minimum - size / 2, minimum + size / 2);

    // Add galaxy node component
    GalaxyNodeComponent::Iterator galaxyNode = entity->addComponent<GalaxyNodeComponent>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = size.length() / 2;

    // Create the stars
    if (!rootNode && galaxyNode->radius < minimumNodeRadiusWithStars)
    {
        // Add the mesh component for the star field meshes
        MeshComponent::Iterator mesh = entity->addComponent<MeshComponent>();
        generateStars(galaxyNode, galaxy, boundingBox, mesh);
    }

    // Activate and return the entity
    entity->activate();
    return entity;
}

void GalaxySystem::adaptGalaxyNode(Vector3 cameraPosition, Entity::Iterator entity)
{
    // Get the galaxy node component
    GalaxyNodeComponent::Iterator galaxyNode = entity->component<GalaxyNodeComponent>();
    if (galaxyNode)
    {
        // Get the transform component
        TransformComponent::Iterator transform = entity->component<TransformComponent>();
        if (transform)
        {
            SpiralGalaxyComponent::Iterator galaxy = galaxyNode->galaxy;

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
    GalaxyNodeComponent::Iterator galaxyNode = entity->component<GalaxyNodeComponent>();
    if (galaxyNode && galaxyNode->split)
    {
        entity->destroyAllChildren();
        galaxyNode->split = false;
    }
}

void GalaxySystem::splitGalaxyNode(Entity::Iterator entity)
{
    // If the node is not split and is not at the maximum level
    GalaxyNodeComponent::Iterator galaxyNode = entity->component<GalaxyNodeComponent>();
    if (galaxyNode && !galaxyNode->split && galaxyNode->radius > minimumNodeRadius)
    {
        Entity::Iterator parent = entity->iterator();

        // Get the bounding box component
        BoundingBoxComponent::Iterator boundingBox = entity->component<BoundingBoxComponent>();
        if (boundingBox)
        {
            SpiralGalaxyComponent::Iterator galaxy = galaxyNode->galaxy;

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
                        Entity::Iterator child = createGalaxyNode(galaxy, size, localPosition, parentGlobalPosition, false);
                        parent->addChild(*child);
                    }
                }
            }

            galaxyNode->split = true;
        }
    }
}

double GalaxySystem::createSeedUniformValue(RandomSeed seed) const
{
    return Random(seed).next(-100000.0, 100000.0);
}

void GalaxySystem::onComponentAdded(SpiralGalaxyComponent::Iterator spiralGalaxy)
{
    generateSpiralGalaxy(spiralGalaxy);
}
