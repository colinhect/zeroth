///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"
#include "Components/ProxyGalaxyComponent.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT ProxyGalaxySystem :
    public System<ProxyGalaxySystem, Components<ProxyGalaxyComponent>>
{
public:
    ProxyGalaxySystem(Engine& engine, Scene& scene);

    /// \property
    Path baseGalaxyScene;

private:
    void onComponentAdded(ProxyGalaxyComponent::Iterator proxyGalaxy) override;
    unsigned computeSkyBoxResolution();
};

}
