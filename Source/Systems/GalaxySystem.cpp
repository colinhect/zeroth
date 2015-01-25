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
    _assetCache(engine.assetCache())
{
    AssetCache& assetCache = engine.assetCache();
    _coloredLineShader = assetCache.getHandle<Shader>("Hect/ColoredLine.shader");
}

void GalaxySystem::tick(double timeStep)
{
    (void)timeStep;

    // If there is an active camera
    CameraSystem& cameraSystem = scene().system<CameraSystem>();
    Camera::Iterator activeCamera = cameraSystem.activeCamera();
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

void GalaxySystem::onComponentAdded(Galaxy::Iterator galaxy)
{
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
    for (int x = 0; x < rootNodeCount; ++x)
    {
        for (int y = 0; y < rootNodeCount; ++y)
        {
            Vector3 localPosition = minimum + size * Vector3(x, y, 0) + halfSize;
            Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, 0, size, localPosition, Vector3::zero());
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
    boundingBox->extents = AxisAlignedBox(minimum - size / 2, minimum + size / 2);

    // Add galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->addComponent<GalaxyNode>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = size.length() / 2;
    galaxyNode->level = level;

    // Add tempory dust particles
    Mesh::Handle mesh(new Mesh());

    VertexLayout layout;
    layout.addAttribute(VertexAttribute(VertexAttributeSemantic_Position, VertexAttributeType_Float32, 3));
    mesh->setVertexLayout(layout);

    mesh->setPrimitiveType(PrimitiveType_Points);

    MeshWriter writer(*mesh);
    writer.addVertex();
    writer.writeAttributeData(VertexAttributeSemantic_Position, Vector3::zero());
    writer.addIndex(0);

    Material::Handle material(new Material());
    material->setShader(_coloredLineShader);
    material->setUniformValue("color", Color(0, 100, 0));

    Model::Iterator model = entity->addComponent<Model>();
    model->surfaces.push_back(ModelSurface(mesh, material));

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
