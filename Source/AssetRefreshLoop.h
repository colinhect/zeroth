///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/IO/AssetCache.h>
#include <Hect/Logic/Loop.h>

using namespace hect;

class AssetRefreshLoop :
    public Loop,
    public Uncopyable
{
public:
    AssetRefreshLoop(AssetCache& assetCache);

    void fixedUpdate(Real timeStep);

private:
    AssetCache* _assetCache;
};