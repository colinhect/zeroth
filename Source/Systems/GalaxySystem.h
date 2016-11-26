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
#include "Components/GalaxyNodeComponent.h"
#include "Components/SpiralGalaxyComponent.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT GalaxySystem :
    public System<GalaxySystem, Components<SpiralGalaxyComponent>>
{
public:
    GalaxySystem(Engine& engine, Scene& scene);

    void adaptGalaxyNodes();

    /// \property{required}
    Material::Handle starMaterial;

    /// \property{required}
    Shader::Handle topologyShader;

    /// \property{required}
    Shader::Handle generateTopologyShader;

    /// \property{required}
    unsigned topologyTextureResolution;

    /// \property{required}
    Shader::Handle particleShader;

    /// \property{required}
    Shader::Handle generateParticleShader;

    /// \property{required}
    unsigned particleTextureResolution;

    /// \property{required}
    Vector2 spiralDiameterRange;

    /// \property{required}
    Vector2 spiralThicknessRange;

    /// \property{required}
    Vector2 spiralParticleSizeRange;

    /// \property{required}
    double minimumNodeRadius;

    /// \property{required}
    double minimumNodeRadiusWithStars;

    /// \property{required}
    unsigned maxStarsPerNode;

private:
    void generateSpiralGalaxy(SpiralGalaxyComponent::Iterator galaxy);
    void createTopologyMesh(SpiralGalaxyComponent::Iterator galaxy);
    void createParticlesMesh(SpiralGalaxyComponent::Iterator galaxy);
    void generateTopologyTexture(SpiralGalaxyComponent::Iterator galaxy);
    void generateParticleTexture(SpiralGalaxyComponent::Iterator galaxy);
    void createParticleTexturePreviewMesh(SpiralGalaxyComponent::Iterator galaxy);
    void sampleTopology(SpiralGalaxyComponent::Iterator galaxy, BoundingBoxComponent::Iterator boundingBox, Vector3 position, Color& color, double& thickness);
    void generateStars(GalaxyNodeComponent::Iterator galaxyNode, SpiralGalaxyComponent::Iterator galaxy, BoundingBoxComponent::Iterator boundingBox, MeshComponent::Iterator mesh);
    Entity::Iterator createGalaxyNode(SpiralGalaxyComponent::Iterator galaxy, Vector3 size, Vector3 localPosition, Vector3 parentGlobalPosition, bool rootNode);
    void adaptGalaxyNode(Vector3 cameraPosition, Entity::Iterator entity);
    void splitGalaxyNode(Entity::Iterator entity);
    void joinGalaxyNode(Entity::Iterator entity);
    double createSeedUniformValue(RandomSeed seed) const;

    // System overrides
    void onComponentAdded(SpiralGalaxyComponent::Iterator spiralGalaxy) override;
};

}
