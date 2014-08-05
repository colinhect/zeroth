///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothScene.h"

#include "Components/CockpitCamera.h"
#include "Components/PlayerCamera.h"
#include "Components/PlayerShipControl.h"
#include "Components/Ship.h"
#include "Components/Thruster.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/PlayerCameraSystem.h"
#include "Systems/PlayerShipControlSystem.h"

ZerothScene::ZerothScene(Input& input, Renderer& renderer, hect::AssetCache& assetCache) :
    DefaultScene(input, renderer, assetCache)
{
    // Zeroth components
    registerComponent<CockpitCamera>();
    registerComponent<PlayerCamera>();
    registerComponent<PlayerShipControl>();
    registerComponent<Ship>();
    registerComponent<Thruster>();

    // Zeroth system
    addSystem<CockpitCameraSystem>(input);
    addSystem<PlayerCameraSystem>(input);
    addSystem<PlayerShipControlSystem>(system<PhysicsSystem>(), input);

    //system<InputSystem>().loadAxes(*axisData);
}

void ZerothScene::systemUpdate(Real timeStep)
{
    system<CockpitCameraSystem>().update(timeStep);
    system<PlayerCameraSystem>().update(timeStep);
    system<PlayerShipControlSystem>().update(timeStep);
}