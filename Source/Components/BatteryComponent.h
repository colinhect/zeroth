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
class ZEROTH_EXPORT BatteryComponent :
    public Component<BatteryComponent>
{
public:

    ///
    /// The electric potential in volts.
    ///
    /// \property{required}
    double electricPotential { 60.0 };

    ///
    /// The amount of energy the battery contains in megajoules.
    ///
    /// \property {required}
    double energy { 48.0 };

    ///
    /// The maximum amount of energy the battery can contain in megajoules.
    ///
    /// \property {required}
    double maximumEnergy { 48.0 };
};

}
