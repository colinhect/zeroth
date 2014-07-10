///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Listener.h>
#include <Hect/Core/Uncopyable.h>
#include <Hect/Core/TaskPool.h>
#include <Hect/IO/AssetCache.h>
#include <Hect/Logic/Loop.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Logic/Systems/RenderSystem.h>
#include <Hect/Logic/Systems/TransformSystem.h>
#include <Hect/Logic/Systems/BoundingBoxSystem.h>
#include <Hect/Logic/Systems/PhysicsSystem.h>
#include <Hect/Logic/Systems/DebugSystem.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/Graphics/Window.h>
#include <Hect/Input/InputSystem.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Debug/TransformDebugRenderLayer.h>

using namespace hect;

#include "Components/PlayerCamera.h"
#include "Systems/PlayerCameraSystem.h"

class ServerLoop :
    public Loop,
    public Listener<KeyboardEvent>,
    public Uncopyable
{
public:
    ServerLoop(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer);
    ~ServerLoop();

    void fixedUpdate(Real timeStep);
    void frameUpdate(Real delta);

    void receiveEvent(const KeyboardEvent& event);

private:
    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    TaskPool _taskPool;

    Scene _scene;

    Entity::Iter _player;
    Entity::Iter _cube;

    RenderSystem _renderSystem;
    TransformSystem _transformSystem;
    BoundingBoxSystem _boundingBoxSystem;
    PhysicsSystem _physicsSystem;
    DebugSystem _debugSystem;

    PlayerCameraSystem _playerCameraSystem;

    TransformDebugRenderLayer _transformDebugRenderLayer;
    BoundingBoxDebugRenderLayer _boundingBoxDebugRenderLayer;
};