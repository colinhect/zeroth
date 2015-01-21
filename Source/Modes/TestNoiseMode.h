///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "GalaxyGenerator.h"

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
    bool _active { true };

    Mouse& _mouse;
    Keyboard& _keyboard;

    GalaxyGenerator _galaxyGenerator;

    Mesh::Handle _screenMesh;
    Shader::Handle _showGalaxyShader;

    Texture _density;
};

}