///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Concurrency/TaskPool.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/IO/AssetCache.h>
#include <Hect/Input/InputSystem.h>
#include <Hect/Logic/Scene.h>

using namespace hect;

class OrbitScene :
    public Scene
{
public:
    OrbitScene(InputSystem& inputSystem, AssetCache& assetCache, Renderer& renderer);

    void update(Real timeStep);
    void render(Real delta, RenderTarget& target);

private:
    TaskPool _taskPool;
    Task::Handle _physicsTaskHandle;
};