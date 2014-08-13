///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/DefaultScene.h>

using namespace hect;

class ZerothScene :
    public DefaultScene
{
public:
    ZerothScene(Renderer& renderer, RenderTarget& renderTarget, AssetCache& assetCache, const JsonValue& settings);

    void fixedUpdate();
};