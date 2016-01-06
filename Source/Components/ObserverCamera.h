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
class ObserverCamera :
    public Component<ObserverCamera>
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