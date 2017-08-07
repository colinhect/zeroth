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

#include "Components/CelestialObjectComponent.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT CelestialObjectSystem :
    public System<CelestialObjectSystem, Components<CelestialObjectComponent>>
{
public:
    CelestialObjectSystem(Scene& scene);

private:
};

}
