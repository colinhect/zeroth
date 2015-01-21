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

enum GalaxyType
{
    GalaxyType_Spiral
};

class GalaxyGenerator
{
public:
    GalaxyGenerator(Engine& engine);

    void generateDensity(GalaxyType type, RandomSeed seed, Texture& density);

private:
    AssetCache& _assetCache;
    Renderer& _renderer;

    Mesh::Handle _screenMesh;
    Shader::Handle _spiralGalaxyShader;
};

}