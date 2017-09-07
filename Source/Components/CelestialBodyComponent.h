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

/// \component
class ZEROTH_EXPORT CelestialBodyComponent :
    public Component<CelestialBodyComponent>
{
public:

    ///
    /// The mass of the celestial object in solar masses.
    ///
    /// \property
    double mass { 1.0 };

    ///
    /// The velocity of the celestial object in kilometers per second.
    ///
    /// \property
    Vector3 velocity;

};

}
