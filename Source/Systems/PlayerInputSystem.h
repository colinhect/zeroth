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
    public EventListener<KeyboardEvent>
{
public:
    PlayerInputSystem(Engine& engine, Scene& scene);

    void handlePlayerInput(double timeStep);

private:
    void controlPlayerShips(double timeStep);
    void adjustCameraExposure(double timeStep);
    void swapMouseMode();
    void toggleDebugInterface();
    void parseKeyboardShortcut(const KeyboardEvent& event);
    void deactivateScene();

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;

    Keyboard& _keyboard;
    Mouse& _mouse;

    Vector3 _angularInput;
    Vector3 _thrustInput;
};

}
