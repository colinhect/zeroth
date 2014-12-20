///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
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
    PlayerShipControlSystem(Scene& scene);

    void tick(Real timeStep) override;
};

}