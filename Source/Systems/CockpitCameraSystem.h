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

/// \system
class CockpitCameraSystem :
    public System
{
public:
    CockpitCameraSystem(Engine& engine, Scene& scene);

    void tick(Real timeStep) override;
};

}