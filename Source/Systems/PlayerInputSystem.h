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
    PlayerInputSystem(Scene& scene, InputSystem& inputSystem, TransformSystem& transformSystem, Platform& platform);

    void handlePlayerInput(Seconds timeStep, Entity& localPlayerEntity);

private:
    void swapMouseMode();
    void parseKeyboardShortcut(const KeyboardEvent& event);
    void deactivateScene();

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;

    InputSystem& _inputSystem;
    TransformSystem& _transformSystem;

    Keyboard& _keyboard;
    Mouse& _mouse;
};

}
