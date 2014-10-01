///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/SystemRegistry.h>

using namespace hect;

namespace zeroth
{

class CockpitCameraSystem :
    public System
{
public:
    CockpitCameraSystem(World& world);

    void tick(Real timeStep) override;
};

}