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

namespace zeroth
{

enum CelestialObjectType
{
    Star,
    Planetoid,
    Comet,
    Asteroid
};

/// \component
class ZEROTH_EXPORT CelestialObjectComponent :
    public Component<CelestialObjectComponent>
{
public:

    /// \property{enum}
    CelestialObjectType type { CelestialObjectType::Star };

};

}
