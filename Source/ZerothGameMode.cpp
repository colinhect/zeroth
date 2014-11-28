///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/Runtime/Engine.h>

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds(static_cast<Real>(1) / static_cast<Real>(60))),
    _sceneRenderer(engine.renderer(), engine.assetCache())
{
    AssetCache& assetCache = engine.assetCache();
    _scene = assetCache.getHandle<Scene>("Test/Scene.scene", engine);
}

void ZerothGameMode::tick()
{
    _scene->tick(timeStep());
}

void ZerothGameMode::render(RenderTarget& target)
{
    _sceneRenderer.renderScene(*_scene, target);
}