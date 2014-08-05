///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/System.h>

using namespace hect;

class CockpitCameraSystem :
    public System
{
public:
    CockpitCameraSystem(Scene& scene);

    void update();
};