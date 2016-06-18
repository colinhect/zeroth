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
class ZEROTH_EXPORT SpiralGalaxy :
    public Component<SpiralGalaxy>
{
public:

    /// \property
    unsigned seed { 0 };

    double diameter;
    double thickness;
    unsigned density;

    Texture2::Handle topologyTexture;
    Texture2::Handle particleTexture;
};

}
