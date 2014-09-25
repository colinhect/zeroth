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
    encoder << encodeValue("power", power)
        << encodeValue("direction", direction);
}

void Thruster::decode(ObjectDecoder& decoder, AssetCache& assetCache)
{
    if (decoder.hasMember("power"))
    {
        power = decoder.decodeReal("power");
    }

    if (decoder.hasMember("direction"))
    {
        direction = decoder.decodeVector3("direction");
    }
}