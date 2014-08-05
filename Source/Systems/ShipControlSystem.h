///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Entity.h>
#include <Hect/Logic/System.h>

using namespace hect;

class ShipControlSystem :
    public System
{
public:
    ShipControlSystem(Scene& scene);

    void controlShip(Entity& ship, const Vector3& angularAmount, Real thrustAmount, Real timeStep);
};