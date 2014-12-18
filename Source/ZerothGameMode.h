///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
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

    void tick() override;
    void render(RenderTarget& target) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    AssetHandle<Scene> _scene;
    SceneRenderer _sceneRenderer;
};

}