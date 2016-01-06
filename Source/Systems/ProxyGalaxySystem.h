///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/ProxyGalaxy.h"

namespace zeroth
{

/// \system
class ProxyGalaxySystem :
    public System<ProxyGalaxySystem, Components<ProxyGalaxy>>
{
public:
    ProxyGalaxySystem(Engine& engine, Scene& scene);

    void onComponentAdded(ProxyGalaxy::Iterator proxyGalaxy) override;

    /// \property
    Path baseGalaxyScene;

private:
    unsigned computeSkyBoxResolution();

    Engine& _engine;
    AssetCache& _assetCache;
};

}