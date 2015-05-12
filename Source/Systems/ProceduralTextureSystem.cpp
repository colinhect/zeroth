///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ProceduralTextureSystem.h"

using namespace zeroth;

void ProceduralTexture::setResolution(unsigned width, unsigned height)
{
    _width = width;
    _height = height;
}

void ProceduralTexture::setPixelFormat(const PixelFormat& pixelFormat)
{
    _pixelFormat = pixelFormat;
}

void ProceduralTexture::setSeed(RandomSeed seed)
{
    _seed = seed;
}

void ProceduralTexture::render()
{
    *_texture = Texture2(_name, _width, _height, _pixelFormat, TextureFilter::Linear, TextureFilter::Linear, false, false);

    FrameBuffer frameBuffer(_width, _height);
    frameBuffer.attach(FrameBufferSlot::Color0, *_texture);

    Renderer::Frame frame = _renderer->beginFrame(frameBuffer);
    frame.clear();

    frame.setShader(*_shader);
    if (_shader->hasUniform("seed"))
    {
        Random random(_seed);
        double seed = random.next(-10000.0, 10000.0);
        frame.setUniform(_shader->uniform("seed"), seed);
    }

    frame.renderViewport();
}

ProceduralTexture::ProceduralTexture(Renderer& renderer, const std::string& name, Shader& shader, Texture2& texture) :
    _renderer(&renderer),
    _name(name),
    _shader(&shader),
    _texture(&texture)
{
}

ProceduralTextureSystem::ProceduralTextureSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _renderer(engine.renderer())
{
}

ProceduralTexture ProceduralTextureSystem::create(const std::string& name, Shader& shader, Texture2& texture)
{
    return ProceduralTexture(_renderer, name, shader, texture);
}
