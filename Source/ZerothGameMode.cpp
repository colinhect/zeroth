///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include "ZerothWorld.h"

ZerothGameMode::ZerothGameMode()
{
}

ZerothGameMode::~ZerothGameMode()
{
}

void ZerothGameMode::execute()
{
    AssetCache& assetCache = Engine::assetCache();

    AssetHandle<Data> worldData = assetCache.getHandle<Data>("Test/World.world");

    ZerothWorld world;
    world.decodeFromData(*worldData, assetCache);

    while (Engine::handleEvents())
    {
        world.tick();
        Engine::window().swapBuffers();
    }
}