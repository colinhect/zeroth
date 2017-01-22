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
    PlayerInputSystem(Engine& engine, Scene& scene);

    void handlePlayerInput(Seconds timeStep);

private:
    void adjustCameraExposure(Seconds timeStep);
    void swapMouseMode();
    void toggleDebugInterface();
    void parseKeyboardShortcut(const KeyboardEvent& event);
    void deactivateScene();

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;

    Keyboard& _keyboard;
    Mouse& _mouse;
};

}
