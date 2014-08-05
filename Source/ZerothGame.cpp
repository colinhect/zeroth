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
    AssetCache assetCache(storage());

    AssetHandle<Data> sceneData = assetCache.getHandle<Data>("Test/Scene.scene");

    ZerothScene scene(input(), renderer(), assetCache);
    scene.decodeFromData(*sceneData, assetCache);

    playScene(scene);
}