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
class ZEROTH_EXPORT GalaxyImposterCellComponent :
    public Component<GalaxyImposterCellComponent>
{
public:
    unsigned depth { 0 };
    bool split { false };
};

}