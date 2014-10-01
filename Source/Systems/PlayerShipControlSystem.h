///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Systems/ShipControlSystem.h"

using namespace hect;

namespace zeroth
{

class PlayerShipControlSystem :
    public ShipControlSystem
{
public:
    PlayerShipControlSystem(World& world);

    void tick(Real timeStep) override;
};

}