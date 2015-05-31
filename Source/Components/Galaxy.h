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

    /// \property{required}
    std::string name;

    /// \property{required}
    Shader::Handle particleShader;

    /// \property{required}
    Vector2 sizeRange;

    /// \property{required}
    Vector2 brightnessRange;

    /// \property{required}
    unsigned density;

    Texture2::Handle particleTexture;
    Material::Handle particleMaterial;
};

/// \encodable
class StarField :
    public Encodable
{
public:

    /// \property{required}
    std::string name;

    /// \property{required}
    Shader::Handle densityShader;

    /// \property{required}
    std::vector<ParticleLayer> particleLayers;

    /// \property{required}
    unsigned density;

    Texture3::Handle densityTexture;
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
    std::vector<StarField> starFields;
};

}