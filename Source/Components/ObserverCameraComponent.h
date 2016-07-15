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
class ZEROTH_EXPORT ObserverCameraComponent :
    public Component<ObserverCameraComponent>
{
public:

    /// \property
    double speed;

    /// \property
    double lookSpeed;

    /// \property
    double rollSpeed;

    /// \property
    double moveSpeed;
};

}
