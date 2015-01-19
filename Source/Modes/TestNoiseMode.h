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
class TestNoiseMode :
    public Mode,
    public Listener<KeyboardEvent>
{
public:
    TestNoiseMode(Engine& engine);

    bool tick(Engine& engine, double timeStep) override;
    void render(Engine& engine, RenderTarget& target) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    void renderNoise();

    bool _active { true };

    AssetCache& _assetCache;
    Renderer& _renderer;
    Mouse& _mouse;
    Keyboard& _keyboard;

    AssetHandle<Mesh> _screenMesh;
    AssetHandle<Shader> _noiseShader;
    AssetHandle<Shader> _showNoiseShader;

    Texture _noiseTexture;
};

}