///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxySystem.h"

using namespace zeroth;

GalaxySystem::GalaxySystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _assetCache(engine.assetCache()),
    _renderer(engine.renderer()),
    _cameraSystem(scene.system<CameraSystem>())
{
    VertexAttribute position(VertexAttributeSemantic_Position, VertexAttributeType_Float32, 3);
    _particleVertexLayout.addAttribute(position);
    VertexAttribute size(VertexAttributeSemantic_Weight0, VertexAttributeType_Float32, 1);
    _particleVertexLayout.addAttribute(size);
    VertexAttribute rotation(VertexAttributeSemantic_Weight1, VertexAttributeType_Float32, 1);
    _particleVertexLayout.addAttribute(rotation);
    VertexAttribute brightness(VertexAttributeSemantic_Weight2, VertexAttributeType_Float32, 1);
    _particleVertexLayout.addAttribute(brightness);
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
    for (ParticleLayer& particleLayer : galaxy->particleLayers)
    {
        // Generate a particle texture
        particleLayer.texture = Texture::Handle(new Texture());
        generateNoise(galaxy->seed, 512, 512, *particleLayer.generateShader, *particleLayer.texture);

        // Create the particle material
        particleLayer.material = Material::Handle(new Material());
        particleLayer.material->setShader(particleLayer.renderShader);
        particleLayer.material->setUniformValue("particleTexture", particleLayer.texture);
        particleLayer.material->setCullMode(CullMode_None);
    }

    // Compute minimum
    double horizontalRadius = galaxy->horizontalRadius;
    double verticalRadius = galaxy->verticalRadius;
    const Vector3 minimum(-horizontalRadius, -horizontalRadius, -verticalRadius);

    // Compute the radio of horizontal to vertical nodes
    double ratio = horizontalRadius / verticalRadius;
    int rootNodeCount = static_cast<int>(ratio);

    // The size of each root node
    Vector3 size(horizontalRadius * 2.0 / rootNodeCount);
    size.z = verticalRadius * 2.0;
    Vector3 halfSize = size / 2.0;

    // Create the root nodes of the galaxy
    Random random(galaxy->seed);
    for (int x = 0; x < rootNodeCount; ++x)
    {
        for (int y = 0; y < rootNodeCount; ++y)
        {
            Vector3 localPosition = minimum + size * Vector3(x, y, 0) + halfSize;
            Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, 0, size, localPosition, Vector3::zero());
            generateDustParticles(random, galaxy, rootGalaxyNode->component<GalaxyNode>(), size);
            galaxy->entity()->addChild(*rootGalaxyNode);
        }
    }

    // Add the bounding box for the whole galaxy
    Entity::Iterator entity = galaxy->entity();
    entity->addComponent<BoundingBox>();
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

void GalaxySystem::joinGalaxyNode(Entity::Iterator entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && galaxyNode->split)
    {
        entity->destroyAllChildren();
        galaxyNode->split = false;
    }
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

void GalaxySystem::generateDustParticles(Random& random, Galaxy::Iterator galaxy, GalaxyNode::Iterator galaxyNode, const Vector3& size)
{
    Entity::Iterator entity = galaxyNode->entity();
    Model::Iterator model = entity->addComponent<Model>();

    for (ParticleLayer& particleLayer : galaxy->particleLayers)
    {
        Mesh::Handle mesh(new Mesh(particleLayer.name));
        mesh->setVertexLayout(_particleVertexLayout);
        mesh->setPrimitiveType(PrimitiveType_Points);

        MeshWriter writer(*mesh);

        Vector3 halfSize = size / 2;
        for (unsigned i = 0; i < particleLayer.density; ++i)
        {
            Vector3 position = random.next(-halfSize, halfSize);
            double size = random.next(particleLayer.size.x, particleLayer.size.y);
            double rotation = random.next(0.0, 2.0 * pi);
            double brightness = random.next(0.25, 1.75);

            writer.addVertex();
            writer.writeAttributeData(VertexAttributeSemantic_Position, position);
            writer.writeAttributeData(VertexAttributeSemantic_Weight0, size);
            writer.writeAttributeData(VertexAttributeSemantic_Weight1, rotation);
            writer.writeAttributeData(VertexAttributeSemantic_Weight2, brightness);
            writer.addIndex(i);
        }

        model->surfaces.push_back(ModelSurface(mesh, particleLayer.material));
    }
}

void GalaxySystem::generateNoise(RandomSeed seed, unsigned width, unsigned height, Shader& shader, Texture& texture)
{
    texture = Texture("Noise", width, height, PixelType_Float16, PixelFormat_Rgb, TextureFilter_Linear, TextureFilter_Linear, false, false);

    FrameBuffer frameBuffer(width, height);
    frameBuffer.attachTexture(FrameBufferSlot_Color0, texture);

    Renderer::Frame frame = _renderer.beginFrame(frameBuffer);
    frame.clear();
    frame.setShader(shader);

    Random random(seed + 12);

    Uniform& uniform = shader.uniform("seed");
    frame.setUniform(uniform, random.next(0.0, 10000.0));

    frame.renderMesh(*screenMesh);
}