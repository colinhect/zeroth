///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothScene.h"

#include <Hect/Input/Systems/InputSystem.h>

#include "Components/CockpitCamera.h"
#include "Components/PlayerCamera.h"
#include "Components/PlayerShipControl.h"
#include "Components/Ship.h"
#include "Components/Thruster.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/PlayerCameraSystem.h"
#include "Systems/PlayerShipControlSystem.h"

ZerothScene::ZerothScene(Renderer& renderer, RenderTarget& renderTarget, AssetCache& assetCache, const JsonValue& settings) :
    DefaultScene(renderer, renderTarget, assetCache)
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
    for (const JsonValue& axisValue : settings["inputAxes"])
    {
        InputAxis axis;
        axis.decodeFromJsonValue(axisValue);
        inputSystem.addAxis(axis);
    }
}

void ZerothScene::fixedUpdate()
{
    DefaultScene::fixedUpdate();

    system<CockpitCameraSystem>().update();
    system<PlayerCameraSystem>().update();
    system<PlayerShipControlSystem>().update();
}