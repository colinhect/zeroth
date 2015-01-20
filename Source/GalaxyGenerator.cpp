///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxyGenerator.h"

using namespace zeroth;

GalaxyGenerator::GalaxyGenerator(Engine& engine) :
    _assetCache(engine.assetCache()),
    _renderer(engine.renderer())
{
    _screenMesh = _assetCache.getHandle<Mesh>("Hect/Screen.mesh");
    _spiralGalaxyShader = _assetCache.getHandle<Shader>("Galaxy/Noise/Spiral.shader");
}

void GalaxyGenerator::generateDensity(GalaxyType type, RandomSeed seed, Texture& density)
{
    const unsigned size = 1024;

    Timer timer;

    density = Texture("GalaxyDensity", size, size, PixelType_Byte, PixelFormat_Rgba, TextureFilter_Linear, TextureFilter_Linear, false, false);

    FrameBuffer frameBuffer(size, size);
    frameBuffer.attachTexture(FrameBufferSlot_Color0, density);

    {
        Renderer::Frame frame = _renderer.beginFrame(frameBuffer);
        frame.clear();
        frame.setShader(*_spiralGalaxyShader);

        Random random(seed);
        for (int i = 0; i < 12; ++i)
        {
            random.next();
        }

        Uniform& uniform = _spiralGalaxyShader->uniform("seed");
        frame.setUniform(uniform, static_cast<double>(random.next() % 100000) / 6.34);

        frame.renderMesh(*_screenMesh);
    }

    HECT_INFO(format("Generated galaxy density in %ims", timer.elapsed().milliseconds()));
}