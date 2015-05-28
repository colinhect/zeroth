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

    void tick(double timeStep) override;
    void onComponentAdded(Galaxy::Iterator galaxy) override;

    /// \property
    Shader::Handle particleShader;

    /// \property
    unsigned particleResolution { 512 };

    /// \property
    unsigned densityResolution { 32 };

private:
    Entity::Iterator createGalaxyNode(Galaxy::Iterator galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition);
    void adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity);
    void splitGalaxyNode(Entity::Iterator entity);
    void joinGalaxyNode(Entity::Iterator entity);

    void initializeStarLayer(StarLayer& layer, Galaxy::Iterator galaxy);
    void generateStarLayer(StarLayer& layer, Galaxy::Iterator galaxy, BoundingBox::Iterator boundingBox, Model::Iterator model);

    double computeDensity(StarLayer& layer, BoundingBox::Iterator boundingBox, const Vector3& position);

    void renderDensityTexture(StarLayer& layer);
    void renderParticleTexture(RandomSeed seed, StarLayer& layer);

    void createDensityPointsMesh();

    CameraSystem::Handle _cameraSystem;

    Mesh _densityPointsMesh;
};

}