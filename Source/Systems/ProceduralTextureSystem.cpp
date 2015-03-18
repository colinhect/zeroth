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

void ProceduralTexture::setPixelType(PixelType pixelType)
{
    _pixelType = pixelType;
}

void ProceduralTexture::setPixelFormat(PixelFormat pixelFormat)
{
    _pixelFormat = pixelFormat;
}

void ProceduralTexture::setSeed(RandomSeed seed)
{
    _seed = seed;
}

void ProceduralTexture::render()
{
    *_texture = Texture(_name, _width, _height, _pixelType, _pixelFormat, TextureFilter_Linear, TextureFilter_Linear, false, false);

    FrameBuffer frameBuffer(_width, _height);
    frameBuffer.attachTexture(FrameBufferSlot_Color0, *_texture);

    Renderer::Frame frame = _renderer->beginFrame(frameBuffer);
    frame.clear();

    frame.setShader(*_shader);
    if (_shader->hasUniform("seed"))
    {
        Random random(_seed);
        double seed = random.next(-10000.0, 10000.0);
        frame.setUniform(_shader->uniform("seed"), seed);
    }

    frame.renderMesh(*_screenMesh);
}

ProceduralTexture::ProceduralTexture(Renderer& renderer, Mesh& screenMesh, const std::string& name, Shader& shader, Texture& texture) :
    _renderer(&renderer),
    _screenMesh(&screenMesh),
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

ProceduralTexture ProceduralTextureSystem::create(const std::string& name, Shader& shader, Texture& texture)
{
    return ProceduralTexture(_renderer, *screenMesh, name, shader, texture);
}
