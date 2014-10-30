///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/Scene.h>

using namespace hect;

namespace zeroth
{

/// \component
class Ship :
    public Component<Ship>
{
public:
    Ship();

    void encode(Encoder& encoder) const;
    void decode(Decoder& decoder);

    std::string name;
};

}