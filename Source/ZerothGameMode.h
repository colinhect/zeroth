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

    void tick(Real timeStep) override;
    void render(Renderer& renderer, RenderTarget& target) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    Mouse& _mouse;
    Keyboard& _keyboard;
    SceneRenderer _sceneRenderer;
    AssetHandle<Scene> _scene;
};

}