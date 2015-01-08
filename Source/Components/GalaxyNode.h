///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Galaxy.h"

namespace zeroth
{

/// \component
class GalaxyNode :
    public Component<GalaxyNode>
{
public:
    Galaxy::Iterator galaxy;
    bool split { false };
};

}