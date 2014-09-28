///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "Thruster.h"

Thruster::Thruster() :
    power(1.0),
    direction(Vector3::unitZ())
{
}

void Thruster::encode(Encoder& encoder) const
{
    encoder << beginObject()
            << encodeValue("power", power)
            << encodeValue("direction", direction)
            << endObject();
}

void Thruster::decode(Decoder& decoder)
{
    decoder >> beginObject()
            >> decodeValue("power", power)
            >> decodeValue("direction", direction)
            >> endObject();
}