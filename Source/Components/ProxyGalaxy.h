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
class ProxyGalaxy :
    public Component<ProxyGalaxy>
{
public:

    /// \property
    unsigned seed { 0 };

    /// \property
    Vector3 position;
};

}