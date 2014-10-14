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
    _world(engine)
{
    AssetCache& assetCache = engine.assetCache();
    AssetDecoder decoder(assetCache, "Test/World.world");
    decoder >> decodeValue(_world);
}

void ZerothGameMode::tick()
{
    _world.tick(timeStep());
}

void ZerothGameMode::render(RenderTarget& target)
{
    Renderer& renderer = engine().renderer();
    renderer.renderWorld(_world, target);

}