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

struct ParticleLayer
{
    std::string name;
    Shader::Handle renderShader;
    Shader::Handle generateShader;
    Vector2 size;
    unsigned density;
    Texture::Handle texture;
    Material::Handle material;

    friend Encoder& operator<<(Encoder& encoder, const ParticleLayer& particleLayer);
    friend Decoder& operator>>(Decoder& decoder, ParticleLayer& particleLayer);
};

/// \component
class Galaxy :
    public Component<Galaxy>
{
public:

    /// \property
    std::string name;

    /// \property
    unsigned seed;

    /// \property
    double horizontalRadius;

    /// \property
    double verticalRadius;

    /// \property
    unsigned maxLevel;

    /// \property
    std::vector<ParticleLayer> particleLayers;
};

}