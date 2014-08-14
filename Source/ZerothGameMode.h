///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/GameMode.h>

using namespace hect;

class ZerothGameMode :
    public GameMode
{
public:
    ZerothGameMode(Engine& engine);

    void execute();
};