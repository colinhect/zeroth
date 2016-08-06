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
class ZEROTH_EXPORT ProxyGalaxyComponent :
    public Component<ProxyGalaxyComponent>
{
public:

    /// \property
    unsigned seed { 0 };

    /// \property
    Vector3 position;
};

}