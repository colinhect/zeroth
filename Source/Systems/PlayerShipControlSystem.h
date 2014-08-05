///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Systems/ShipControlSystem.h"

using namespace hect;

class PlayerShipControlSystem :
    public ShipControlSystem
{
public:
    PlayerShipControlSystem(Scene& scene);

    void update();
};