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
#include "Components/SpiralGalaxy.h"

namespace zeroth
{

/// \component
class ZEROTH_EXPORT GalaxyNode :
    public Component<GalaxyNode>
{
public:
    SpiralGalaxy::Iterator galaxy;
    double radius { 0 };
    bool split { false };
};

}
