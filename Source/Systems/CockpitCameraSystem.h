///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \system
class CockpitCameraSystem :
    public System<CockpitCameraSystem>
{
public:
    CockpitCameraSystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;
};

}