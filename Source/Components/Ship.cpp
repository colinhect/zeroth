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
    encoder << beginObject()
            << encodeValue("name", name)
            << endObject();
}

void Ship::decode(Decoder& decoder)
{
    decoder >> beginObject()
            >> decodeValue("name", name)
            >> endObject();
}