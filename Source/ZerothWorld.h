///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/DefaultWorld.h>

using namespace hect;

class ZerothWorld :
    public DefaultWorld
{
public:
    ZerothWorld(Renderer& renderer, RenderTarget& renderTarget, AssetCache& assetCache, const JsonValue& settings);

    void fixedUpdate();
};