///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/ComponentRegistry.h>
#include <Hect/Math/Vector3.h>

using namespace hect;

namespace zeroth
{

/// \component
class Thruster :
    public Component<Thruster>
{
public:
    Thruster();

    void encode(Encoder& encoder) const;
    void decode(Decoder& decoder);

    Real power;
    Vector3 direction;
};

}