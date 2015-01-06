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

        // Create the root galaxy node as a child
        Entity::Iterator child = scene().createEntity();

        Transform::Iterator transform = child->addComponent<Transform>();
        transform->localPosition = galaxy->extents.center();

        BoundingBox::Iterator boundingBox = child->addComponent<BoundingBox>();
        boundingBox->adaptive = false;
        boundingBox->extents = galaxy->extents;

        child->activate();

        entity->addChild(*child);
    }
}
