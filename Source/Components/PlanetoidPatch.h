///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Planetoid.h"

namespace zeroth
{

/// \component
class PlanetoidPatch :
    public Component<PlanetoidPatch>
{
public:
    CubeSide cubeSide { CubeSide::PositiveZ };
    double halfSize { 1.0 };
    bool split { false };
};

}