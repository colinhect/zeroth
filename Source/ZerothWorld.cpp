///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothWorld.h"

#include <Hect/Input/Systems/InputSystem.h>

#include "Components/CockpitCamera.h"
#include "Components/PlayerCamera.h"
#include "Components/PlayerShipControl.h"
#include "Components/Ship.h"
#include "Components/Thruster.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/PlayerCameraSystem.h"
#include "Systems/PlayerShipControlSystem.h"

ZerothWorld::ZerothWorld(ZerothGameMode& gameMode) :
    DefaultWorld(gameMode)
{
    // Zeroth components
    registerComponent<CockpitCamera>();
    registerComponent<PlayerCamera>();
    registerComponent<PlayerShipControl>();
    registerComponent<Ship>();
    registerComponent<Thruster>();

    // Zeroth system
    addSystem<CockpitCameraSystem>();
    addSystem<PlayerCameraSystem>();
    addSystem<PlayerShipControlSystem>();

    InputSystem& inputSystem = system<InputSystem>();
    for (const JsonValue& axisValue : gameMode.engine().settings()["inputAxes"])
    {
        InputAxis axis;
        axis.decodeFromJsonValue(axisValue);
        inputSystem.addAxis(axis);
    }
}

void ZerothWorld::fixedUpdate()
{
    DefaultWorld::fixedUpdate();

    system<CockpitCameraSystem>().update();
    system<PlayerCameraSystem>().update();
    system<PlayerShipControlSystem>().update();
}