///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \component
class SpiralGalaxy :
    public Component<SpiralGalaxy>
{
public:

    /// \property
    unsigned seed { 0 };

    double diameter;
    double thickness;
    unsigned density;

    std::array<double, 4> variations;

    Color bulgeColor;
    Color primaryColor;
    Color secondaryColor;

    Texture2::Handle topologyTexture;
};

}