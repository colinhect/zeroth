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

namespace zeroth
{

/// \system
class ZEROTH_EXPORT PlayerInputSystem :
    public System<PlayerInputSystem>,
    public EventListener<KeyboardEvent>
{
public:
    PlayerInputSystem(Scene& scene, CameraSystem& cameraSystem, InputSystem& inputSystem, Keyboard& keyboard, Mouse& mouse);

    void handlePlayerInput(Seconds timeStep);

private:
    void adjustCameraExposure(Seconds timeStep);
    void swapMouseMode();
    void parseKeyboardShortcut(const KeyboardEvent& event);
    void deactivateScene();

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;

    CameraSystem& _cameraSystem;
    InputSystem& _inputSystem;

    Keyboard& _keyboard;
    Mouse& _mouse;
};

}
