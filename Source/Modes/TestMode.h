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

/// \mode
class TestMode :
    public Mode,
    public Listener<KeyboardEvent>
{
public:
    TestMode(Engine& engine);

    bool tick(Engine& engine, double timeStep) override;
    void render(Engine& engine, RenderTarget& target) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    bool _active { true };

    Mouse& _mouse;
    Keyboard& _keyboard;

    AssetHandle<Scene> _scene;
};

}