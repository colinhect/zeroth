///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

class ShipControlSystem :
    public System
{
public:
    ShipControlSystem(Engine& engine, Scene& scene);

    void controlShip(Entity& ship, const Vector3& angularAmount, Real thrustAmount, Real timeStep);
};

}