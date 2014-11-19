///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "Ship.h"

using namespace zeroth;

Ship::Ship() :
    name("<unnamed>")
{
}

void Ship::encode(Encoder& encoder) const
{
    encoder << encodeValue("name", name);
}

void Ship::decode(Decoder& decoder)
{
    decoder >> decodeValue("name", name);
}