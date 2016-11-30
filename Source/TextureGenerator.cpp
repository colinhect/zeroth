///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "TextureGenerator.h"

using namespace zeroth;

static const Path GlowParticleShaderPath("TextureGenerator/GlowParticle.shader");
static const Path SpiralTopologyShaderPath("TextureGenerator/SpiralTopology.shader");

TextureGenerator::TextureGenerator(Renderer& renderer, AssetCache& assetCache) :
    _renderer(&renderer),
    _glowParticleShader(assetCache.getHandle<Shader>(GlowParticleShaderPath)),
    _spiralTopologyShader(assetCache.getHandle<Shader>(SpiralTopologyShaderPath))
{
}

Texture2::Handle TextureGenerator::generate(const GlowParticle& glowParticle)
{
    const unsigned resolution = glowParticle.resolution;

    Texture2::Handle texture(new Texture2(glowParticle.name, resolution, resolution));
    texture->setPixelFormat(PixelFormat::Rg8);
    texture->setMipmapped(false);
    texture->setWrapped(false);
    
    FrameBuffer frameBuffer(resolution, resolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer::Frame frame = _renderer->beginFrame(frameBuffer);

    Shader& shader = *_glowParticleShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), createSeedUniformValue(glowParticle.seed));
    frame.renderViewport();

    return texture;
}

Texture2::Handle TextureGenerator::generate(const SpiralTopology& spiralTopology)
{
    const unsigned resolution = spiralTopology.resolution;

    Texture2::Handle texture(new Texture2(spiralTopology.name, resolution, resolution));
    texture->setPixelFormat(PixelFormat::Rgba32);
    texture->setMipmapped(false);
    texture->setWrapped(false);

    FrameBuffer frameBuffer(resolution, resolution);
    frameBuffer.attach(FrameBufferSlot::Color0, *texture);

    Renderer::Frame frame = _renderer->beginFrame(frameBuffer);

    Shader& shader = *_spiralTopologyShader;
    frame.setShader(shader);
    frame.setUniform(shader.uniform("seed"), createSeedUniformValue(spiralTopology.seed));

    frame.renderViewport();

    return texture;
}

double TextureGenerator::createSeedUniformValue(RandomSeed seed) const
{
    return Random(seed).next(-100000.0, 100000.0);
}
