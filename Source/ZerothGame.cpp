///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGame.h"

#include "ZerothWorld.h"

ZerothGame::ZerothGame() :
    Game("Zeroth", "zeroth/Settings.json")
{
}

void ZerothGame::execute()
{
    AssetCache assetCache;

    AssetHandle<Data> worldData = assetCache.getHandle<Data>("Test/World.world");

    ZerothWorld world(renderer(), window(), assetCache, settings());
    world.decodeFromData(*worldData, assetCache);

    playWorld(world);
}