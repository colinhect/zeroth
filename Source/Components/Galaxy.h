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
    Shader::Handle particleShader;

    /// \property
    Shader::Handle generateDustParticleShader;

    /// \property
    Vector2 particleSize;

    /// \property
    unsigned particleDensity;

    Texture::Handle particleTexture;
    Material::Handle particleMaterial;
};

}