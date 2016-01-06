///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \component
class Planet :
    public Component<Planet>
{
public:

    /// \property
    std::string name { "Unknown Planet" };

    /// \property
    double meanRadius { 0 };

    /// \property
    unsigned patchResolution { 16 };

    /// \property
    Material::Handle patchMaterial;
};

}