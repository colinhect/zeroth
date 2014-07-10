///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Scene.h>
#include <Hect/Logic/System.h>
#include <Hect/Input/InputSystem.h>

using namespace hect;

#include "Components/PlayerCamera.h"

class PlayerCameraSystem :
    public System
{
public:
    PlayerCameraSystem(Scene& scene, InputSystem& inputSystem);

    void update(Real timeStep);

private:
    Mouse* _mouse;

    const InputAxis* _viewX;
    const InputAxis* _viewY;

    const InputAxis* _moveX;
    const InputAxis* _moveY;

    const InputAxis* _roll;

    Real _speed;
};