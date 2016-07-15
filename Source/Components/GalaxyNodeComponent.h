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
#include "Components/SpiralGalaxyComponent.h"

namespace zeroth
{

/// \component
class ZEROTH_EXPORT GalaxyNodeComponent :
    public Component<GalaxyNodeComponent>
{
public:
    SpiralGalaxyComponent::Iterator galaxy;
    double radius { 0 };
    bool split { false };
};

}
