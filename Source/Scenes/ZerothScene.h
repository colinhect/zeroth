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

#include "Systems/ChaseCameraSystem.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/GalaxySystem.h"
#include "Systems/HudSystem.h"
#include "Systems/ObserverCameraSystem.h"
#include "Systems/PlanetSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/ProxyGalaxySystem.h"
#include "Systems/ShipControlSystem.h"

namespace zeroth
{

/// \scene
class ZEROTH_EXPORT ZerothScene :
    public DefaultScene
{
public:
    ZerothScene(Engine& engine);

    virtual void tick(double timeStep) override;

private:
    ChaseCameraSystem::Handle _chaseCameraSystem;
    CockpitCameraSystem::Handle _cockpitCameraSystem;
    GalaxySystem::Handle _galaxySystem;
    HudSystem::Handle _hudSystem;
    ObserverCameraSystem::Handle _observerCameraSystem;
    PlanetSystem::Handle _planetSystem;
    PlayerInputSystem::Handle _playerInputSystem;
    ProxyGalaxySystem::Handle _proxyGalaxySystem;
    ShipControlSystem::Handle _shipControlSystem;
};

}
