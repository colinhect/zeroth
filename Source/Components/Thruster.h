///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Scene.h>
#include <Hect/Math/Vector3.h>

using namespace hect;

namespace zeroth
{

/// \component
class Thruster :
    public Component<Thruster>
{
public:

    /// \property
    Real power { 1 };

    /// \property
    Vector3 direction { Vector3::unitZ() };
};

}