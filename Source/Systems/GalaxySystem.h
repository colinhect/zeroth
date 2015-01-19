///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Galaxy.h"
#include "Components/GalaxyNode.h"

namespace zeroth
{

/// \system
class GalaxySystem :
    public System,
    public Listener<ComponentEvent<Galaxy>>
{
public:
    GalaxySystem(Engine& engine, Scene& scene);

    void tick(Engine& engine, double timeStep) override;
    void receiveEvent(const ComponentEvent<Galaxy>& event) override;

private:
    void initializeGalaxy(const Galaxy::Iterator& galaxy);
    Entity::Iterator createGalaxyNode(const Galaxy::Iterator& galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition);
    void adaptGalaxyNode(const Vector3& cameraPosition, const Entity::Iterator& entity);
    void splitGalaxyNode(const Entity::Iterator& entity);
    void joinGalaxyNode(const Entity::Iterator& entity);
};

}