///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/IO/AssetDecoder.h>
#include <Hect/Logic/Systems/InputSystem.h>
#include <Hect/Runtime/Engine.h>

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds(static_cast<Real>(1) / static_cast<Real>(60))),
    _scene(engine),
    _sceneRenderer(engine.renderer(), engine.assetCache())
{
    AssetCache& assetCache = engine.assetCache();
    AssetDecoder decoder(assetCache, "Test/Scene.scene");
    decoder >> decodeValue(_scene);
}

void ZerothGameMode::tick()
{
    _scene.tick(timeStep());
}

void ZerothGameMode::render(RenderTarget& target)
{
    _sceneRenderer.renderScene(_scene, target);
}