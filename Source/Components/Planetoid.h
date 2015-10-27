///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \component
class Planetoid :
    public Component<Planetoid>
{
public:

    /// \property
    std::string name { "Unknown Planetoid" };

    /// \property
    double meanRadius { 0 };
};

}