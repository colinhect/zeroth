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

    CameraSystem& cameraSystem = scene().system<CameraSystem>();
    Camera::Iterator activeCamera = cameraSystem.activeCamera();
    if (activeCamera)
    {
        Vector3 observerPosition = activeCamera->position;
        for (Galaxy& galaxy : scene().components<Galaxy>())
        {
            Entity::Iterator galaxyEntity = galaxy.entity();
            for (Entity& child : galaxyEntity->children())
            {
                Entity::Iterator rootGalaxyNode = child.iterator();
                adaptGalaxyNode(observerPosition, rootGalaxyNode);
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
    // The number of root nodes along each axis
    IntVector3 rootNodes = galaxy->rootNodes;

    // The size of a root node
    Vector3 rootNodeSize = galaxy->extents.size() / rootNodes;

    // Create the root nodes of the galaxy
    for (int x = 0; x < rootNodes.x; ++x)
    {
        for (int y = 0; y < rootNodes.y; ++y)
        {
            for (int z = 0; z < rootNodes.z; ++z)
            {
                Vector3 delta(x, y, z);
                Vector3 minimum = galaxy->extents.minimum() + rootNodeSize * delta;
                AxisAlignedBox extents(minimum, minimum + rootNodeSize);
                galaxy->entity()->addChild(*createGalaxyNode(0, galaxy, extents));
            }
        }
    }

    // Split all root nodes to the initial level
    Entity::Iterator galaxyEntity = galaxy->entity();
    for (Entity& child : galaxyEntity->children())
    {
        Entity::Iterator rootGalaxyNode = child.iterator();
        for (unsigned i = 0; i < galaxy->initialLevel; ++i)
        {
            splitGalaxyNode(rootGalaxyNode);
        }
    }
}

Entity::Iterator GalaxySystem::createGalaxyNode(unsigned level, const Galaxy::Iterator& galaxy, const AxisAlignedBox& extents)
{
    // Create the galaxy node entity
    Entity::Iterator entity = scene().createEntity();

    // Add transform component
    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->localPosition = extents.center();

    // Add bounding box component
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();
    boundingBox->adaptive = false;
    boundingBox->extents = extents;

    // Add galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->addComponent<GalaxyNode>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = extents.size().length() / 2;
    galaxyNode->level = level;

    // Activate and return the entity
    entity->activate();
    return entity;
}

void GalaxySystem::splitGalaxyNode(const Entity::Iterator& entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode->split)
    {
        for (Entity& child : entity->children())
        {
            splitGalaxyNode(child.iterator());
        }
    }
    else if (galaxyNode->level < galaxyNode->galaxy->maxLevel)
    {
        Entity::Iterator parent = entity->iterator();
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (galaxyNode && boundingBox && !galaxyNode->split)
        {
            unsigned level = galaxyNode->level + 1;
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            const Vector3 center = boundingBox->extents.center();
            const Vector3& minimum = boundingBox->extents.minimum();
            const Vector3& maximum = boundingBox->extents.maximum();

            const Vector3 half = (maximum - minimum) * Real(0.5);
            const Vector3 halfX = half * Vector3(1, 0, 0);
            const Vector3 halfY = half * Vector3(0, 1, 0);
            const Vector3 halfZ = half * Vector3(0, 0, 1);
            const Vector3 halfXy = half * Vector3(1, 1, 0);
            const Vector3 halfXz = half * Vector3(1, 0, 1);
            const Vector3 halfZy = half * Vector3(0, 1, 1);

            // Create the child nodes
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum, center)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfX, center + halfX)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfY, center + halfY)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfZ, center + halfZ)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfXy, center + halfXy)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfXz, center + halfXz)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(minimum + halfZy, center + halfZy)));
            parent->addChild(*createGalaxyNode(level, galaxy, AxisAlignedBox(center, maximum)));

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

void GalaxySystem::adaptGalaxyNode(const Vector3& observerPosition, const Entity::Iterator& entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode)
    {
        Transform::Iterator transform = entity->component<Transform>();
        if (transform)
        {
            Real distance = (observerPosition - transform->globalPosition).length();
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
                    adaptGalaxyNode(observerPosition, child.iterator());
                }
            }
        }
    }
}
