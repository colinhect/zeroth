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

#include "Scenes/GalacticScene.h"

#include "Systems/ChaseCameraSystem.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/HudSystem.h"
#include "Systems/ObserverCameraSystem.h"
#include "Systems/PlanetSystem.h"
#include "Systems/PlayerInputSystem.h"
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

    /// \property{required}
    GalacticScene::Handle galacticScene;

private:
    ChaseCameraSystem::Handle _chaseCameraSystem;
    CockpitCameraSystem::Handle _cockpitCameraSystem;
    HudSystem::Handle _hudSystem;
    ObserverCameraSystem::Handle _observerCameraSystem;
    PlayerInputSystem::Handle _playerInputSystem;
    ShipControlSystem::Handle _shipControlSystem;
};

}
