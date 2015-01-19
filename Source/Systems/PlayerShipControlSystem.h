///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Systems/ShipControlSystem.h"

namespace zeroth
{

/// \system
class PlayerShipControlSystem :
    public ShipControlSystem
{
public:
    PlayerShipControlSystem(Engine& engine, Scene& scene);

    void tick(Engine& engine, double timeStep) override;
};

}