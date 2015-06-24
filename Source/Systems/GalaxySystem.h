///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/SpiralGalaxy.h"
#include "Components/GalaxyNode.h"

namespace zeroth
{

/// \system
class GalaxySystem :
    public System<GalaxySystem, Components<SpiralGalaxy>>,
            public Listener<KeyboardEvent>
{
public:
    GalaxySystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(SpiralGalaxy::Iterator galaxy) override;
    void receiveEvent(const KeyboardEvent& event) override;

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
    void generateSpiralGalaxy(SpiralGalaxy::Iterator galaxy);
    void createTopologyMesh(SpiralGalaxy::Iterator galaxy);
    void createParticlesMesh(SpiralGalaxy::Iterator galaxy);
    void generateTopologyTexture(SpiralGalaxy::Iterator galaxy);
    void generateParticleTexture(SpiralGalaxy::Iterator galaxy);
    void sampleTopology(SpiralGalaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, const Vector3& position, Color& color, double& thickness);
    void generateStars(GalaxyNode::Iterator galaxyNode, SpiralGalaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model);


    Entity::Iterator createGalaxyNode(SpiralGalaxy::Iterator galaxy, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition, bool rootNode);
    void adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity);
    void splitGalaxyNode(Entity::Iterator entity);
    void joinGalaxyNode(Entity::Iterator entity);

    double createSeedUniformValue(RandomSeed seed) const;

    Renderer& _renderer;

    CameraSystem::Handle _cameraSystem;
};

}