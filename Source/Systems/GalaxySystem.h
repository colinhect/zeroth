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

    void tick(Real timeStep) override;
    void receiveEvent(const ComponentEvent<Galaxy>& event) override;

private:
    Entity::Iterator createGalaxyNode(const Galaxy::Iterator& galaxy, const AxisAlignedBox& extents);
    void splitGalaxyNode(Entity& entity);
    void joinGalaxyNode(Entity& entity);
};

}