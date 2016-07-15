///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

/// \component
class ZEROTH_EXPORT PlanetComponent :
    public Component<PlanetComponent>
{
public:

    /// \property
    std::string name { "Unknown PlanetComponent" };

    /// \property
    double meanRadius { 0 };

    /// \property
    unsigned patchResolution { 16 };

    /// \property
    Material::Handle patchMaterial;
};

}
