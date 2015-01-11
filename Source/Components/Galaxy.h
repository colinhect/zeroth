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
class Galaxy :
    public Component<Galaxy>
{
public:

    /// \property
    std::string name;

    /// \property
    AxisAlignedBox extents;

    /// \property
    IntVector3 rootNodes;

    /// \property
    unsigned maxLevel;
};

}