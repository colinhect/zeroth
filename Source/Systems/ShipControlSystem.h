///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \system
class ShipControlSystem :
    public System<ShipControlSystem>
{
public:
    ShipControlSystem(Engine& engine, Scene& scene);

    void controlShip(Entity& ship, const Vector3& angularAmount, double thrustAmount, double timeStep);

private:
    TransformSystem::Handle _transformSystem;
    PhysicsSystem::Handle _physicsSystem;
};

}