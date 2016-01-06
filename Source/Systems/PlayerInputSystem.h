///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Systems/ShipControlSystem.h"

namespace zeroth
{

/// \system
class PlayerInputSystem :
    public System<PlayerInputSystem>,
    public Listener<KeyboardEvent>
{
public:
    PlayerInputSystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;
    void receiveEvent(const KeyboardEvent& event) override;

private:
    void swapMouseMode();
    void toggleDebugInterface();
    void deactivateScene();

    Keyboard& _keyboard;
    Mouse& _mouse;

    CameraSystem::Handle _cameraSystem;
    DebugSystem::Handle _debugSystem;
    InputSystem::Handle _inputSystem;
    ShipControlSystem::Handle _shipControlSystem;
};

}