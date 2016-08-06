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

/// \system
class ZEROTH_EXPORT CockpitCameraSystem :
    public System<CockpitCameraSystem>
{
public:
    CockpitCameraSystem(Engine& engine, Scene& scene);
};

}
