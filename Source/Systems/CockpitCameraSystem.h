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

#include "Components/CockpitCamera.h"

using namespace hect;

class CockpitCameraSystem :
    public System,
    public Listener<KeyboardEvent>
{
public:
    CockpitCameraSystem(Scene& scene, Input& input);
    ~CockpitCameraSystem();

    void update(Real timeStep);

    void receiveEvent(const KeyboardEvent& event);

private:
    Input* _input;

    const InputAxis* _viewX;
    const InputAxis* _viewY;
};