///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/GameMode.h>
#include <Hect/Logic/World.h>

using namespace hect;

class ZerothGameMode :
    public GameMode
{
public:
    ZerothGameMode(Engine& engine);
    ~ZerothGameMode();

    void tick();

private:
    World _world;
};