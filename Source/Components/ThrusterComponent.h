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
class ZEROTH_EXPORT ThrusterComponent :
    public Component<ThrusterComponent>
{
public:

    /// \property
    double power { 1 };

    /// \property
    Vector3 direction { Vector3::UnitZ };
};

}
