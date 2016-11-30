///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

class ZEROTH_EXPORT TextureGenerator
{
public:
    struct ZEROTH_EXPORT GlowParticle
    {
        Name name { "GlowParticle" };
        RandomSeed seed;
        unsigned resolution { 512 };
    };
    
    struct ZEROTH_EXPORT SpiralTopology
    {
        Name name { "SpiralTopology" };
        RandomSeed seed;
        unsigned resolution { 512 };
    };

    TextureGenerator(Renderer& renderer, AssetCache& assetCache);

    Texture2::Handle generate(const GlowParticle& glowParticle);
    Texture2::Handle generate(const SpiralTopology& spiralTopology);

private:
    double createSeedUniformValue(RandomSeed seed) const;

    Renderer* _renderer;
    Shader::Handle _glowParticleShader;
    Shader::Handle _spiralTopologyShader;
};

}
