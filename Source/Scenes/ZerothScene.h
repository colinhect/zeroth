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

/// \scene
class ZEROTH_EXPORT ZerothScene :
    public DefaultScene
{
public:
    ZerothScene(Engine& engine);
};

}
