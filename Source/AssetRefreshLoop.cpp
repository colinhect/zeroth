///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "AssetRefreshLoop.h"

AssetRefreshLoop::AssetRefreshLoop(AssetCache& assetCache) :
    Loop(TimeSpan::fromSeconds(1)),
    _assetCache(&assetCache)
{
}
void AssetRefreshLoop::fixedUpdate(Real timeStep)
{
    //_assetCache->refresh();
}