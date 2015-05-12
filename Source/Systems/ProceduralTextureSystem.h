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

class ProceduralTexture
{
    friend class ProceduralTextureSystem;
public:
    void setResolution(unsigned width, unsigned height);
    void setPixelFormat(const PixelFormat& pixelFormat);
    void setSeed(RandomSeed seed);

    void render();

private:
    ProceduralTexture(Renderer& renderer, const std::string& name, Shader& shader, Texture2& texture);

    Renderer* _renderer;
    std::string _name;
    Shader* _shader;
    Texture2* _texture;
    unsigned _width { 256 };
    unsigned _height { 256 };
    PixelFormat _pixelFormat;
    RandomSeed _seed { 42 };
};

/// \system
class ProceduralTextureSystem :
    public System<ProceduralTextureSystem>
{
public:
    ProceduralTextureSystem(Engine& engine, Scene& scene);

    ProceduralTexture create(const std::string& name, Shader& shader, Texture2& texture);

private:
    Renderer& _renderer;
};

}