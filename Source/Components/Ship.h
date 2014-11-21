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

    /// \property
    std::string name;
};

}