///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Component.h>

using namespace hect;

class Ship :
    public Component<Ship>
{
public:
    Ship();

    void encode(Encoder& encoder) const;
    void decode(ObjectDecoder& decoder, AssetCache& assetCache);

    std::string name;
};