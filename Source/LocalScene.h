///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Concurrency/TaskPool.h>
#include <Hect/Core/Engine.h>
#include <Hect/Core/Uncopyable.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/Systems/DebugRenderSystem.h>
#include <Hect/Event/Listener.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/Graphics/Window.h>
#include <Hect/Graphics/Systems/PhysicallyBasedRenderSystem.h>
#include <Hect/IO/AssetCache.h>
#include <Hect/Input/InputSystem.h>
#include <Hect/Logic/Loop.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>
#include <Hect/Spacial/Systems/TransformSystem.h>
#include <Hect/Spacial/Systems/BoundingBoxSystem.h>

#include "Components/PlayerCamera.h"
#include "Systems/PlayerCameraSystem.h"

using namespace hect;

class LocalScene :
    public Scene
{
public:
    LocalScene(Engine& engine);

    void update(Real timeStep);
    void render(Real delta, RenderTarget& target);

private:
    TaskPool _taskPool;

    PhysicallyBasedRenderSystem _renderSystem;
    DebugRenderSystem _debugRenderSystem;
    TransformSystem _transformSystem;
    BoundingBoxSystem _boundingBoxSystem;
    PhysicsSystem _physicsSystem;

    PlayerCameraSystem _playerCameraSystem;

    TransformDebugRenderLayer _transformDebugRenderLayer;
    BoundingBoxDebugRenderLayer _boundingBoxDebugRenderLayer;
};