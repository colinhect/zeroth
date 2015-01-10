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

/// \gamemode
class ZerothGameMode :
    public GameMode,
    public Listener<KeyboardEvent>
{
public:
    ZerothGameMode(Engine& engine);

    void tick(Engine& engine, Real timeStep) override;
    void render(Engine& engine, RenderTarget& target) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    void drawLoadingScreen(Engine& engine);

    Mouse& _mouse;
    Keyboard& _keyboard;

    AssetHandle<Scene> _scene;
    AssetHandle<Font> _font;
};

}