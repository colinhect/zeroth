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

#include "Systems/GalaxySystem.h"
#include "Systems/ObserverCameraSystem.h"

namespace zeroth
{

/// \scene
class ZEROTH_EXPORT CelestialScene :
    public DefaultScene
{
public:
    CelestialScene(Engine& engine);

    virtual void tick(double timeStep) override;

private:
    GalaxySystem& _galaxySystem;
    ObserverCameraSystem& _observerCameraSystem;
};

}
