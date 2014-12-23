///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
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
    Real speed;

    /// \property
    Real lookSpeed;

    /// \property
    Real rollSpeed;

    /// \property
    Real moveSpeed;
};

}