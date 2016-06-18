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

enum ThrusterType
{
    PrimaryEngine,
    ReactionControl
};

/// \component
class ZEROTH_EXPORT Thruster :
    public Component<Thruster>
{
public:

    ///
    /// \property{enum}
    ThrusterType type { ThrusterType::PrimaryEngine };

    /// \property
    double power { 1 };

    /// \property
    Vector3 direction { Vector3::UnitZ };
};

}
