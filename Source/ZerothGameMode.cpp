///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/IO/Data.h>
#include <Hect/IO/JsonDecoder.h>
#include <Hect/Logic/Systems/InputSystem.h>
#include <Hect/Runtime/Engine.h>

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds((Real)1 / (Real)60)),
    _world(engine)
{
    RenderSystem& renderSystem = engine.renderSystem();
    renderSystem.addWorld(_world);

    AssetCache& assetCache = engine.assetCache();

    AssetCache::SelectDirectoryScope scope(assetCache, "Test");
    AssetHandle<JsonValue> worldJsonValue = assetCache.getHandle<JsonValue>("World.world");
    JsonDecoder decoder(*worldJsonValue, assetCache);
    decoder >> decodeValue(_world);
}

ZerothGameMode::~ZerothGameMode()
{
    RenderSystem& renderSystem = engine().renderSystem();
    renderSystem.removeWorld(_world);
}

void ZerothGameMode::tick()
{
    _world.tick(timeStep());
}