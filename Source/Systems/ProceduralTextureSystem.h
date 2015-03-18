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
    void setPixelType(PixelType pixelType);
    void setPixelFormat(PixelFormat pixelFormat);
    void setSeed(RandomSeed seed);

    void render();

private:
    ProceduralTexture(Renderer& renderer, Mesh& screenMesh, const std::string& name, Shader& shader, Texture& texture);

    Renderer* _renderer;
    Mesh* _screenMesh;
    std::string _name;
    Shader* _shader;
    Texture* _texture;
    unsigned _width { 256 };
    unsigned _height { 256 };
    PixelType _pixelType { PixelType_Byte };
    PixelFormat _pixelFormat { PixelFormat_Rgba };
    RandomSeed _seed { 42 };
};

/// \system
class ProceduralTextureSystem :
    public System<ProceduralTextureSystem>
{
public:
    ProceduralTextureSystem(Engine& engine, Scene& scene);

    ProceduralTexture create(const std::string& name, Shader& shader, Texture& texture);

    /// \property
    Mesh::Handle screenMesh;

private:
    Renderer& _renderer;
};

}