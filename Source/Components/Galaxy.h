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
    Shader::Handle renderShader;

    /// \property
    Shader::Handle generateShader;

    /// \property
    Vector2 size;

    /// \property
    unsigned density;

    Texture::Handle texture;
    Material::Handle material;
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