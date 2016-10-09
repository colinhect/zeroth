///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "SystemicScene.h"

#include "Components/GalaxyNodeComponent.h"
#include "Components/ObserverCameraComponent.h"
#include "Components/ProxyGalaxyComponent.h"

#include "Systems/GalaxySystem.h"
#include "Systems/ObserverCameraSystem.h"

using namespace zeroth;

SystemicScene::SystemicScene(Engine& engine) :
    DefaultScene(engine),
    _galaxySystem(createSystem<GalaxySystem>()),
    _observerCameraSystem(createSystem<ObserverCameraSystem>())
{
}

void SystemicScene::tick(double timeStep)
{
    DefaultScene::preTick(timeStep);

    _observerCameraSystem->tickObservers(timeStep);
    _galaxySystem->adaptGalaxyNodes();

    DefaultScene::postTick(timeStep);
}
