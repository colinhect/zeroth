///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \system
class CockpitCameraSystem :
    public System<>
{
public:
    CockpitCameraSystem(Engine& engine, Scene& scene);

    void tick(Engine& engine, double timeStep) override;
};

}