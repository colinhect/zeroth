///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Real.h>
#include <Hect/Logic/Scene.h>

using namespace hect;

namespace zeroth
{

/// \system
class PlayerCameraSystem :
    public System
{
public:
    PlayerCameraSystem(Scene& scene);

    void tick(Real timeStep) override;

private:
    Real _speed;
};

}