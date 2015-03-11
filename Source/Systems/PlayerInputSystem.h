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
class PlayerInputSystem :
    public System<PlayerInputSystem>
{
public:
    PlayerInputSystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;
};

}