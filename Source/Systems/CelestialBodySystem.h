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

#include "Components/CelestialBodyComponent.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT CelestialBodySystem :
    public System<CelestialBodySystem, Components<CelestialBodyComponent>>
{
public:
    CelestialBodySystem(Scene& scene);

    // ComponentListener overrides
    void onComponentAdded(CelestialBodyComponent& component) override;
    void onComponentRemoved(CelestialBodyComponent& component) override;

private:
    void updateOrbit(Entity& celestialBody);
    Entity& determineParentBody(Entity& celestialBody);
};

}
