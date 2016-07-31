///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"
#include "Systems/ShipControlSystem.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT PlayerInputSystem :
    public System<PlayerInputSystem>,
    public Listener<KeyboardEvent>
{
public:
    PlayerInputSystem(Engine& engine, Scene& scene);

    void tick(double timeStep);
    void receiveEvent(const KeyboardEvent& event) override;

private:
    void swapMouseMode();
    void toggleDebugInterface();
    void toggleDebugRendering();
    void parseKeyboardShortcut(const KeyboardEvent& event);

    void deactivateScene();

    Keyboard& _keyboard;
    Mouse& _mouse;

    CameraSystem::Handle _cameraSystem;
    DebugSystem::Handle _debugSystem;
    InputSystem::Handle _inputSystem;
    ShipControlSystem::Handle _shipControlSystem;
};

}
