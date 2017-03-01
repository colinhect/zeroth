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
    Name name;
    GalaxyType type { GalaxyType::Spiral };
};

struct ZEROTH_EXPORT GalaxyImposter
{
    Vector3 position;
    Color color;
    double size;
};

class ZEROTH_EXPORT GalaxyGenerator
{
public:

    //void generateGalaxyImposters(unsigned layer, const AxisAlignedBox& bounds, std::vector<GalaxyImposter>& galaxyImposters);
    //void generateGalaxies
};

}
