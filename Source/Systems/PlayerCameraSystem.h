///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Real.h>
#include <Hect/Logic/SystemRegistry.h>

using namespace hect;

namespace zeroth
{

class PlayerCameraSystem :
    public System
{
public:
    PlayerCameraSystem(World& world);

    void tick(Real timeStep) override;

private:
    Real _speed;
};

}