///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/DefaultWorld.h>

#include "ZerothGameMode.h"

using namespace hect;

class ZerothWorld :
    public DefaultWorld
{
public:
    ZerothWorld();

    void fixedUpdate();
};