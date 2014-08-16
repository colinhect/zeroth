///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/LightProbe.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Logic/GameMode.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>
#include <Hect/Runtime/Engine.h>
#include <Hect/Spacial/Components/BoundingBox.h>
#include <Hect/Spacial/Components/Transform.h>
#include <Hect/Spacial/Systems/BoundingBoxSystem.h>
#include <Hect/Spacial/Systems/TransformSystem.h>

#include "Components/CockpitCamera.h"
#include "Components/PlayerCamera.h"
#include "Components/PlayerShipControl.h"
#include "Components/Ship.h"
#include "Components/Thruster.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/PlayerCameraSystem.h"
#include "Systems/PlayerShipControlSystem.h"


ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds((Real)1 / (Real)60))
{
    engine.renderSystem().addWorld(_world);

    _world.addSystem<BoundingBoxSystem>();
    _world.addSystem<InputSystem>();
    _world.addSystem<PhysicsSystem>();
    _world.addSystem<TransformSystem>();
    //
    _world.addSystem<CockpitCameraSystem>();
    _world.addSystem<PlayerCameraSystem>();
    _world.addSystem<PlayerShipControlSystem>();

    InputSystem& inputSystem = _world.system<InputSystem>();
    for (const JsonValue& axisValue : engine.settings()["inputAxes"])
    {
        InputAxis axis;
        axis.decodeFromJsonValue(axisValue);
        inputSystem.addAxis(axis);
    }

    //

    AssetHandle<Data> worldData = engine.assetCache().getHandle<Data>("Test/World.world");
    _world.decodeFromData(*worldData, engine.assetCache());
}

ZerothGameMode::~ZerothGameMode()
{
    engine().renderSystem().removeWorld(_world);
}

void ZerothGameMode::tick()
{
    _world.system<InputSystem>().tick(timeStep().seconds());
    _world.system<PhysicsSystem>().updateTransforms();
    _world.system<TransformSystem>().update();
    _world.system<BoundingBoxSystem>().update();

    _world.system<CockpitCameraSystem>().tick(timeStep().seconds());
    _world.system<PlayerCameraSystem>().tick(timeStep().seconds());
    _world.system<PlayerShipControlSystem>().tick(timeStep().seconds());

    _world.system<PhysicsSystem>().simulate(timeStep());
}