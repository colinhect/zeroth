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

void Ship::encode(Encoder& encoder) const
{
    encoder << encodeValue("name", name);
}

void Ship::decode(ObjectDecoder& decoder, AssetCache& assetCache)
{
    if (decoder.hasMember("name"))
    {
        name = decoder.decodeString("name");
    }
}