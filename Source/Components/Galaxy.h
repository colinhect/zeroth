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

enum class GalaxyType
{
    //Elliptical,
    //Lenticular,
    Spiral
};

/// \component
class Galaxy :
    public Component<Galaxy>
{
public:

    /// \property
    unsigned seed { 0 };

    GalaxyType type;
    double diameter;
    double thickness;
    double eccentricity;
    double armThickness;
};

}