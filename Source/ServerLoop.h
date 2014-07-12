///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Concurrency/TaskPool.h>
#include <Hect/Core/Uncopyable.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/Systems/DebugSystem.h>
#include <Hect/Event/Listener.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/Graphics/Window.h>
#include <Hect/Graphics/Systems/RenderSystem.h>
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
    Entity::Iter _frigate;

    RenderSystem _renderSystem;
    TransformSystem _transformSystem;
    BoundingBoxSystem _boundingBoxSystem;
    PhysicsSystem _physicsSystem;
    DebugSystem _debugSystem;

    PlayerCameraSystem _playerCameraSystem;

    TransformDebugRenderLayer _transformDebugRenderLayer;
    BoundingBoxDebugRenderLayer _boundingBoxDebugRenderLayer;
};