///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "LocalScene.h"

#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

#include "RegisterComponents.h"

LocalScene::LocalScene(Engine& engine) :
    Scene(engine, registerComponents),
    _taskPool(4),
    _renderSystem(*this),
    _debugRenderSystem(*this),
    _transformSystem(*this),
    _boundingBoxSystem(*this),
    _physicsSystem(*this, _taskPool),
    _playerCameraSystem(*this),
    _transformDebugRenderLayer(engine.assetCache()),
    _boundingBoxDebugRenderLayer(engine.assetCache())
{
    _debugRenderSystem.addRenderLayer(Key_F5, _transformDebugRenderLayer);
    _debugRenderSystem.addRenderLayer(Key_F6, _boundingBoxDebugRenderLayer);
}

void LocalScene::update(Real timeStep)
{
    _physicsSystem.endAsynchronousUpdate();

    _playerCameraSystem.update(timeStep);
    _renderSystem.updateActiveCamera();
    _transformSystem.update();
    _boundingBoxSystem.update();

    _physicsSystem.beginAsynchronousUpdate(timeStep, 4);
}

void LocalScene::render(Real delta, RenderTarget& target)
{
    delta;

    _renderSystem.renderAll(target);
    _debugRenderSystem.renderAll(target);
}