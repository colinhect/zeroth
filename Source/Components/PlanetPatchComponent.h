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
class ZEROTH_EXPORT PlanetPatchComponent :
    public Component<PlanetPatchComponent>
{
public:
    CubeSide cubeSide { CubeSide::PositiveZ };
    double halfSize { 1.0 };
    bool split { false };
    unsigned depth { 0 };
};

}
