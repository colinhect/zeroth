///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothScene.h"

#include "Components/ChaseCameraComponent.h"
#include "Components/CockpitCameraComponent.h"
#include "Components/GalaxyNodeComponent.h"
#include "Components/ObserverCameraComponent.h"
#include "Components/PlanetComponent.h"
#include "Components/PlanetPatchComponent.h"
#include "Components/PlayerShipControlComponent.h"
#include "Components/ProxyGalaxyComponent.h"
#include "Components/ShipComponent.h"
#include "Components/SpiralGalaxyComponent.h"
#include "Components/ThrusterComponent.h"

#include "Systems/ChaseCameraSystem.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/GalaxySystem.h"
#include "Systems/HudSystem.h"
#include "Systems/ObserverCameraSystem.h"
#include "Systems/PlanetSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/ProxyGalaxySystem.h"
#include "Systems/ShipControlSystem.h"

using namespace zeroth;

ZerothScene::ZerothScene(Engine& engine) :
    DefaultScene(engine),
    _chaseCameraSystem(createSystem<ChaseCameraSystem>()),
    _cockpitCameraSystem(createSystem<CockpitCameraSystem>()),
    _galaxySystem(createSystem<GalaxySystem>()),
    _hudSystem(createSystem<HudSystem>()),
    _observerCameraSystem(createSystem<ObserverCameraSystem>()),
    _planetSystem(createSystem<PlanetSystem>()),
    _playerInputSystem(createSystem<PlayerInputSystem>()),
    _proxyGalaxySystem(createSystem<ProxyGalaxySystem>()),
    _shipControlSystem(createSystem<ShipControlSystem>())
{
}

void ZerothScene::tick(double timeStep)
{
    DefaultScene::preTick(timeStep);

    _observerCameraSystem->tick(timeStep);
    _playerInputSystem->tick(timeStep);
    _cockpitCameraSystem->tick(timeStep);
    _chaseCameraSystem->tick(timeStep);
    _hudSystem->tick(timeStep);
    _galaxySystem->tick(timeStep);
    _planetSystem->tick(timeStep);

    DefaultScene::postTick(timeStep);
}
