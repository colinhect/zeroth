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
class ZEROTH_EXPORT StarComponent :
    public Component<StarComponent>
{
public:

    ///
    /// The absolute magnitude of the star.  Range for main sequence stars is
    /// -10 to 15.
    ///
    /// \property
    double absoluteMagnitude { 0.0 };

    ///
    /// The temperature of the star in kelvin.  Range for main sequence stars
    /// is 2,000K to 30,000K.
    ///
    /// \property
    double temperature { 0.0 };

};

}
