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
class StarLayer :
    public Encodable
{
public:

    /// \property{required}
    std::string name;

    /// \property{required}
    Shader::Handle proceduralParticleShader;

    /// \property{required}
    Shader::Handle proceduralDensityShader;

    /// \property{required}
    Vector2 sizeRange;

    /// \property{required}
    Vector2 brightnessRange;

    /// \property{required}
    unsigned density;

    /// \property{required}
    double verticleRadius;

    /// \property{required}
    double verticleRadiusFalloff;

    Texture2::Handle densityTexture;
    Image::Handle densityImage;
    Texture2::Handle particleTexture;
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
    std::vector<StarLayer> starLayers;
};

}