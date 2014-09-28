///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Component.h>
#include <Hect/Math/Vector3.h>

using namespace hect;

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