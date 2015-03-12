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
    GalaxySystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(Galaxy::Iterator galaxy) override;

    /// \property
    Mesh::Handle screenMesh;

private:
    Entity::Iterator createGalaxyNode(Galaxy::Iterator galaxy, unsigned level, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition);
    void adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity);
    void splitGalaxyNode(Entity::Iterator entity);
    void joinGalaxyNode(Entity::Iterator entity);
    void generateDustParticles(Random& random, Galaxy::Iterator galaxy, GalaxyNode::Iterator galaxyNode, const Vector3& size);
    void generateNoise(RandomSeed seed, unsigned width, unsigned height, Shader& shader, Texture& texture);

    AssetCache& _assetCache;
    Renderer& _renderer;

    CameraSystem::Handle _cameraSystem;

    VertexLayout _particleVertexLayout;
};

}