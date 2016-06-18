///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT ShipControlSystem :
    public System<ShipControlSystem>
{
public:
    ShipControlSystem(Engine& engine, Scene& scene);

    void controlShip(Entity& ship, const Vector3& directionalThrust, const Vector3& angularThrust, double timeStep);

    void debugTick(double timeStep) override;

private:
    DebugSystem::Handle _debugSystem;
    TransformSystem::Handle _transformSystem;
    PhysicsSystem::Handle _physicsSystem;
};

}
