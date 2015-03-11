///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \system
class GameplaySystem :
    public System<GameplaySystem>,
    public Listener<KeyboardEvent>
{
public:
    GameplaySystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;
    void receiveEvent(const KeyboardEvent& event) override;

private:
    Mouse& _mouse;
};

}