///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Galaxy.h"
#include "Components/GalaxyNode.h"

namespace zeroth
{

/// \system
class GalaxySystem :
    public System<GalaxySystem, Components<Galaxy>>
{
public:
    GalaxySystem(Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(Galaxy::Iterator galaxy) override;

    /// \property{required}
    Shader::Handle particleShader;

    /// \property{required}
    Material::Handle starMaterial;

    /// \property
    unsigned particleResolution { 512 };

    /// \property
    unsigned densityResolution { 32 };

private:
    Entity::Iterator createGalaxyNode(Galaxy::Iterator galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition);
    void adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity);
    void splitGalaxyNode(Entity::Iterator entity);
    void joinGalaxyNode(Entity::Iterator entity);

    void initializeStarField(StarField& starField, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model);
    void generateStarField(StarField& starField, GalaxyNode::Iterator galaxyNode, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model);
    void generateParticleLayer(StarField& starField, ParticleLayer& particleLayer, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model);
    void renderDensityTexture(StarField& starField);
    void renderParticleTexture(RandomSeed seed, ParticleLayer& particleLayer);
    double computeDensity(StarField& starField, BoundingBox::Iterator boundingBox, const Vector3& position);

    Mesh createDensityPointsMesh() const;

    CameraSystem::Handle _cameraSystem;

    Mesh _densityPointsMesh;
};

}