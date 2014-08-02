///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "Ship.h"

Ship::Ship() :
    name("Unknown")
{
}

void Ship::encode(ObjectEncoder& encoder) const
{
    encoder.encodeString("name", name);
}

void Ship::decode(ObjectDecoder& decoder, AssetCache& assetCache)
{
    if (decoder.hasMember("power"))
    {
        name = decoder.decodeString("name");
    }
}