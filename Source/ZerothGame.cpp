///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGame.h"

#include "ZerothScene.h"

ZerothGame::ZerothGame() :
    Game("Zeroth", "zeroth/Settings.json")
{
}

void ZerothGame::execute()
{
    AssetCache assetCache(fileSystem());

    AssetHandle<Data> sceneData = assetCache.getHandle<Data>("Test/Scene.scene");

    ZerothScene scene(inputDevices(), renderer(), window(), assetCache, settings());
    scene.decodeFromData(*sceneData, assetCache);

    playScene(scene);
}