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

/// \encodable
class ParticleLayer :
    public Encodable
{
public:

    /// \property
    std::string name;

    /// \property
    Shader::Handle generateParticleShader;

    /// \property
    Shader::Handle generateDensityShader;

    /// \property
    Vector2 sizeRange;

    /// \property
    Vector2 brightnessRange;

    /// \property
    unsigned density;

    Texture::Handle densityTexture;
    Texture::Handle particleTexture;
    Material::Handle particleMaterial;
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