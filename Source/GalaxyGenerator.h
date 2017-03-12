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

enum class GalaxyType
{
    Spiral
};

struct ZEROTH_EXPORT Galaxy
{
    Vector3 position;
    Color color;
    double size { 0.0 };
    RandomSeed seed { 0 };
};

struct ZEROTH_EXPORT GalaxyDescriptor
{
    Name name;
    GalaxyType type { GalaxyType::Spiral };
};

class ZEROTH_EXPORT GalaxyGenerator
{
public:

    void generateGalaxies(unsigned layer, const AxisAlignedBox& bounds, std::vector<Galaxy>& galaxies);

    GalaxyDescriptor generateGalaxyDescriptor(const Galaxy& galaxy) const;
};

}
