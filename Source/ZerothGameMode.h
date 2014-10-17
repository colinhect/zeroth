///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Logic/GameMode.h>
#include <Hect/Logic/Scene.h>

using namespace hect;

namespace zeroth
{

/// \gamemode
class ZerothGameMode :
    public GameMode
{
public:
    ZerothGameMode(Engine& engine);

    void tick() override;
    void render(RenderTarget& target) override;

private:
    Scene _scene;
};

}