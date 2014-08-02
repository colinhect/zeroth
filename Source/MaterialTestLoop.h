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

#include "OrbitScene.h"

using namespace hect;

class MaterialTestLoop :
    public Loop,
    public Listener<KeyboardEvent>,
    public Uncopyable
{
public:
    MaterialTestLoop(Engine& engine);
    ~MaterialTestLoop();

    void fixedUpdate(Real timeStep);
    void frameUpdate(Real delta);

    void receiveEvent(const KeyboardEvent& event);

private:
    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    TaskPool _taskPool;

    OrbitScene _scene;

    Entity::Handle _player;
    Entity::Handle _test;
};