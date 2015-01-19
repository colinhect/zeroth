///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "TestNoiseMode.h"

using namespace zeroth;

TestNoiseMode::TestNoiseMode(Engine& engine) :
    _assetCache(engine.assetCache()),
    _renderer(engine.renderer()),
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard())
{
    _screenMesh = _assetCache.getHandle<Mesh>("Hect/Screen.mesh");
    _noiseShader = _assetCache.getHandle<Shader>("Noise/NoiseTest.shader");
    _showNoiseShader = _assetCache.getHandle<Shader>("Noise/ShowNoise.shader");

    renderNoise();

    _keyboard.addListener(*this);
}

bool TestNoiseMode::tick(Engine& engine, double timeStep)
{
    return _active;
}

void TestNoiseMode::render(Engine& engine, RenderTarget& target)
{
    Renderer& renderer = engine.renderer();
    {
        Renderer::Frame frame = renderer.beginFrame(target);
        frame.clear();
        frame.setShader(*_showNoiseShader);
        frame.setUniform(_showNoiseShader->uniform("noiseTexture"), _noiseTexture);
        frame.renderMesh(*_screenMesh);
    }
}

void TestNoiseMode::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown)
    {
        if (event.key == Key_Esc)
        {
            _active = false;
        }
    }
}

void TestNoiseMode::renderNoise()
{
    unsigned size = 1024;

    Timer timer;

    _noiseTexture = Texture("Noise", size, size, PixelType_Byte, PixelFormat_Rgba, TextureFilter_Linear, TextureFilter_Linear, false, false);

    FrameBuffer frameBuffer(size, size);
    frameBuffer.attachTexture(FrameBufferSlot_Color0, _noiseTexture);

    {
        Renderer::Frame frame = _renderer.beginFrame(frameBuffer);
        frame.clear();
        frame.setShader(*_noiseShader);
        frame.renderMesh(*_screenMesh);
    }

    HECT_INFO(format("Generated noise in %ims", timer.elapsed().milliseconds()));
}
