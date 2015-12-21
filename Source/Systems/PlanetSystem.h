///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Planet.h"
#include "Components/PlanetPatch.h"

namespace zeroth
{

/// \system
class PlanetSystem :
    public System<PlanetSystem, Components<Planet>>
{
public:
    PlanetSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(Planet::Iterator planet) override;

private:
    void split(PlanetPatch::Iterator patch);

    Entity::Iterator createPatch(Entity::Iterator parent, CubeSide cubeSide, const Vector3& relativePosition);
    Entity::Iterator createRootPatch(Planet::Iterator planet, CubeSide cubeSide);

    Mesh::Handle buildPatchMesh(Planet::Iterator planet, PlanetPatch::Iterator patch, const Vector3& relativePosition);

    static Vector3 morphPointToSphere(const Vector3& point, const Vector3& relativePosition, double radius);
    static Vector3 projectUnitCubeToSphere(const Vector3& point);

    static const Vector3& cubeSideUpVector(CubeSide cubeSide);
    static const Vector3& cubeSideRightVector(CubeSide cubeSide);

    AssetCache& _assetCache;

    BoundingBoxSystem::Handle _boundingBoxSystem;
    CameraSystem::Handle _cameraSystem;
    TransformSystem::Handle _transformSystem;

    Planet::Iterator _planet;
};

}