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
}

void GalaxySystem::receiveEvent(const ComponentEvent<Galaxy>& event)
{
    // If a galaxy component was added to an entity
    if (event.type == ComponentEventType_Add)
    {
        Entity::Iterator entity = event.entity().iterator();
        Galaxy::Iterator galaxy = entity->component<Galaxy>();

        // Create the root galaxy node
        Entity::Iterator rootNode = createGalaxyNode(galaxy, galaxy->extents);
        splitGalaxyNode(*rootNode);

        entity->addChild(*rootNode);
    }
}

Entity::Iterator GalaxySystem::createGalaxyNode(const Galaxy::Iterator& galaxy, const AxisAlignedBox& extents)
{
    // Create the root galaxy node as a child
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

    entity->activate();
    return entity;
}

void GalaxySystem::splitGalaxyNode(Entity& entity)
{
    Entity::Iterator parent = entity.iterator();

    GalaxyNode::Iterator galaxyNode = entity.component<GalaxyNode>();
    BoundingBox::Iterator boundingBox = entity.component<BoundingBox>();
    if (galaxyNode && boundingBox && !galaxyNode->split)
    {
        Galaxy::Iterator galaxy = galaxyNode->galaxy;

        Vector3 center = boundingBox->extents.center();
        const Vector3& minimum = boundingBox->extents.minimum();
        const Vector3& maximum = boundingBox->extents.maximum();
        
        Vector3 half = (maximum - minimum) * Real(0.5);
        Vector3 halfX = half * Vector3::unitX();
        Vector3 halfY = half * Vector3::unitY();
        Vector3 halfZ = half * Vector3::unitZ();

        // Create the child nodes
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum, center)));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(1, 0, 0), center + half * Vector3(1, 0, 0))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(0, 1, 0), center + half * Vector3(0, 1, 0))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(0, 0, 1), center + half * Vector3(0, 0, 1))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(1, 1, 0), center + half * Vector3(1, 1, 0))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(1, 0, 1), center + half * Vector3(1, 0, 1))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(minimum + half * Vector3(1, 1, 1), center + half * Vector3(1, 1, 1))));
        parent->addChild(*createGalaxyNode(galaxy, AxisAlignedBox(center, maximum)));

        galaxyNode->split = true;
    }
}

void GalaxySystem::joinGalaxyNode(Entity& entity)
{
    GalaxyNode::Iterator galaxyNode = entity.component<GalaxyNode>();
    if (galaxyNode && galaxyNode->split)
    {
        entity.destroyAllChildren();
    }
}
