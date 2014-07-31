///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "OrbitScene.h"

#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/LightProbe.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

OrbitScene::OrbitScene(InputSystem& inputSystem, AssetCache& assetCache, Renderer& renderer) :
    _taskPool(4)
{
    // Register components
    registerComponent<Camera>();
    registerComponent<DirectionalLight>();
    registerComponent<LightProbe>();
    registerComponent<Model>();
    registerComponent<SkyBox>();
    registerComponent<RigidBody>();
    registerComponent<Transform>();
    registerComponent<BoundingBox>();
    registerComponent<PlayerCamera>();

    // Add systems
    addSystem<PhysicallyBasedRenderSystem>(assetCache, renderer);
    addSystem<DebugRenderSystem>(inputSystem, assetCache, renderer);
    addSystem<TransformSystem>();
    addSystem<BoundingBoxSystem>();
    addSystem<PhysicsSystem>();
    addSystem<PlayerCameraSystem>(inputSystem);
}

void OrbitScene::update(Real timeStep)
{
    if (_physicsUpdateTask)
    {
        _physicsUpdateTask->wait();
        system<PhysicsSystem>().updateTransforms();
    }

    system<PlayerCameraSystem>().update(timeStep);
    system<PhysicallyBasedRenderSystem>().updateActiveCamera();
    system<TransformSystem>().update();
    system<BoundingBoxSystem>().update();

    _physicsUpdateTask = _taskPool.enqueue([this, timeStep]
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