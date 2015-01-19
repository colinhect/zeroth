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
class Thruster :
    public Component<Thruster>
{
public:

    /// \property
    double power { 1 };

    /// \property
    Vector3 direction { Vector3::unitZ() };
};

}