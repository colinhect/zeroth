///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \component
class PlanetPatch :
    public Component<PlanetPatch>
{
public:
    CubeSide cubeSide { CubeSide::PositiveZ };
    double halfSize { 1.0 };
    bool split { false };
    unsigned depth { 0 };
};

}