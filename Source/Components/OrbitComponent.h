///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2017 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

///
/// The orbit of a satellite object around a celestial body.
///
/// \component
class ZEROTH_EXPORT OrbitComponent :
    public Component<OrbitComponent>
{
public:

    ///
    /// The parent body of the orbit.
    Entity::Handle parentBody;
};

}
