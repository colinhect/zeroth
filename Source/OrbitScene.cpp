///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "OrbitScene.h"

#include <Hect/Debug/Systems/DebugRenderSystem.h>
#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/LightProbe.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Graphics/Systems/PhysicallyBasedRenderSystem.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>
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

OrbitScene::OrbitScene(Input& input, AssetCache& assetCache, Renderer& renderer) :
    _taskPool(4)
{
    // Hect components
    registerComponent<Camera>();
    registerComponent<DirectionalLight>();
    registerComponent<LightProbe>();
    registerComponent<Model>();
    registerComponent<SkyBox>();
    registerComponent<RigidBody>();
    registerComponent<Transform>();
    registerComponent<BoundingBox>();

    // Hect systems
    addSystem<PhysicallyBasedRenderSystem>(assetCache, renderer);
    addSystem<DebugRenderSystem>(input, assetCache, renderer);
    addSystem<TransformSystem>();
    addSystem<BoundingBoxSystem>();
    addSystem<PhysicsSystem>();

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
}

void OrbitScene::update(Real timeStep)
{
    if (_physicsTaskHandle)
    {
        _physicsTaskHandle->wait();
        system<PhysicsSystem>().updateTransforms();
    }
    system<TransformSystem>().update();
    system<BoundingBoxSystem>().update();

    system<PhysicallyBasedRenderSystem>().updateActiveCamera();

    system<CockpitCameraSystem>().update(timeStep);
    system<PlayerCameraSystem>().update(timeStep);
    system<PlayerShipControlSystem>().update(timeStep);

    system<TransformSystem>().update();
    system<BoundingBoxSystem>().update();

    _physicsTaskHandle = _taskPool.enqueue([this, timeStep]
        {
            system<PhysicsSystem>().simulate(timeStep, 4);
        }
    );
}

void OrbitScene::render(Real delta, RenderTarget& target)
{
    delta;

    system<PhysicallyBasedRenderSystem>().renderAll(target);
    system<DebugRenderSystem>().renderAll(target);
}