///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include "ZerothWorld.h"

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine)
{
}

void ZerothGameMode::execute()
{
    AssetCache& assetCache = engine().assetCache();
    AssetHandle<Data> worldData = assetCache.getHandle<Data>("Test/World.world");

    ZerothWorld world(*this);
    world.decodeFromData(*worldData, assetCache);

    while (engine().handleEvents())
    {
        world.tick();
        engine().window().swapBuffers();
    }
}