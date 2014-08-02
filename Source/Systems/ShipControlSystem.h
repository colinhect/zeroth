///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Scene.h>
#include <Hect/Logic/System.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>

using namespace hect;

class ShipControlSystem :
    public System
{
public:
    ShipControlSystem(Scene& scene, PhysicsSystem& physicsSystem);
    ~ShipControlSystem();

    void controlShip(Entity& ship, const Vector3& angularAmount, Real thrustAmount, Real timeStep);

private:
    PhysicsSystem* _physicsSystem;
};