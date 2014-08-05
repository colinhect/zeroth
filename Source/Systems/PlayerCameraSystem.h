///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Event/Listener.h>
#include <Hect/Input/Input.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Logic/System.h>

#include "Components/PlayerCamera.h"

using namespace hect;

class PlayerCameraSystem :
    public System,
    public Listener<KeyboardEvent>
{
public:
    PlayerCameraSystem(Scene& scene, Input& input);
    ~PlayerCameraSystem();

    void update(Real timeStep);

    void receiveEvent(const KeyboardEvent& event);

private:
    Input* _input;

    const InputAxis* _viewX;
    const InputAxis* _viewY;

    const InputAxis* _moveX;
    const InputAxis* _moveY;

    const InputAxis* _roll;

    Real _speed;
};