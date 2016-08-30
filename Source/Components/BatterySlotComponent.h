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
class ZEROTH_EXPORT BatterySlotComponent :
    public Component<BatterySlotComponent>
{
public:

    ///
    /// The entity of the battery currently fitted in the slot.
    Entity::Handle battery;
};

}
