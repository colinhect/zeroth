///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Real.h>
#include <Hect/Logic/System.h>

using namespace hect;

class PlayerCameraSystem :
    public System
{
public:
    PlayerCameraSystem(World& world);

    void update();

private:
    Real _speed;
};