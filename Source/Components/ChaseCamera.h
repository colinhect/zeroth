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
class ChaseCamera :
    public Component<ChaseCamera>
{
public:

    /// \property{required}
    double distance { 10.0 };
};

}