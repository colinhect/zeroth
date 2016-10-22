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

    void controlShip(Entity& ship, Vector3 directionalThrust, Vector3 angularThrust, double timeStep);

    void renderDebugGeometry();
};

}
