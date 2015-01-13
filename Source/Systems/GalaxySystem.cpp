///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxySystem.h"

using namespace zeroth;

GalaxySystem::GalaxySystem(Engine& engine, Scene& scene) :
    System(scene)
{
    (void)engine;

    scene.components<Galaxy>().addListener(*this);
}

void GalaxySystem::tick(Real timeStep)
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

void GalaxySystem::receiveEvent(const ComponentEvent<Galaxy>& event)
{
    // If a galaxy component was added to an entity
    if (event.type == ComponentEventType_Add)
    {
        // Initialize the galaxy
        Galaxy::Iterator galaxy = event.entity->component<Galaxy>();
        initializeGalaxy(galaxy);
    }
}

void GalaxySystem::initializeGalaxy(const Galaxy::Iterator& galaxy)
{
    IntVector3 rootNodes = galaxy->rootNodes;
    const Vector3& minimum = galaxy->extents.minimum();
    Vector3 size = galaxy->extents.size() / rootNodes;
    Vector3 halfSize = size / 2;
    Vector3 parentGlobalPosition = galaxy->extents.center();

    // Create the root nodes of the galaxy
    for (int x = 0; x < rootNodes.x; ++x)
    {
        for (int y = 0; y < rootNodes.y; ++y)
        {
            for (int z = 0; z < rootNodes.z; ++z)
            {
                Vector3 localPosition = minimum + size * Vector3(x, y, z) + halfSize;
                Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, 0, size, localPosition, parentGlobalPosition);
                galaxy->entity()->addChild(*rootGalaxyNode);
            }
        }
    }
}

Entity::Iterator GalaxySystem::createGalaxyNode(const Galaxy::Iterator& galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition)
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

    // Add model component
    Model::Iterator model = entity->addComponent<Model>();

    // Add galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->addComponent<GalaxyNode>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = size.length() / 2;
    galaxyNode->level = level;

    // Activate and return the entity
    entity->activate();
    return entity;
}

void GalaxySystem::splitGalaxyNode(const Entity::Iterator& entity)
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
            std::vector<int> values{ -1, 1 };
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

void GalaxySystem::joinGalaxyNode(const Entity::Iterator& entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && galaxyNode->split)
    {
        entity->destroyAllChildren();
        galaxyNode->split = false;
    }
}

void GalaxySystem::adaptGalaxyNode(const Vector3& cameraPosition, const Entity::Iterator& entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode)
    {
        Transform::Iterator transform = entity->component<Transform>();
        if (transform)
        {
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            Real distance = (cameraPosition - transform->globalPosition).length();
            if (galaxyNode->split && distance > galaxyNode->radius * 2)
            {
                joinGalaxyNode(entity);
            }
            else if (!galaxyNode->split && distance < galaxyNode->radius * Real(1.9))
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
