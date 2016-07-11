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
#include "Components/Planet.h"
#include "Components/PlanetPatch.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT PlanetSystem :
    public System<PlanetSystem, Components<Planet>>
{
public:
    PlanetSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(Planet::Iterator planet) override;

    void adapt(Vector3 cameraPosition, Entity::Iterator entity);

private:

    void split(PlanetPatch::Iterator patch);
    void join(PlanetPatch::Iterator patch);

    void createPlanet(Planet::Iterator planet);

    Entity::Iterator createPatch(Entity::Iterator parent, CubeSide cubeSide, Vector3 localPosition, Vector3 parentGlobalPosition);
    Entity::Iterator createRootPatch(Planet::Iterator planet, CubeSide cubeSide);

    Mesh::Handle buildPatchMesh(Planet::Iterator planet, PlanetPatch::Iterator patch, Vector3 localPosition, Vector3 parentGlobalPosition);

    static Vector3 morphPointToSphere(Vector3 point, Vector3 localPosition, double radius);
    static Vector3 projectUnitCubeToSphere(Vector3 point);

    static Vector3 cubeSideUpVector(CubeSide cubeSide);
    static Vector3 cubeSideRightVector(CubeSide cubeSide);

    AssetCache& _assetCache;

    BoundingBoxSystem::Handle _boundingBoxSystem;
    CameraSystem::Handle _cameraSystem;
    TransformSystem::Handle _transformSystem;

    Planet::Iterator _planet;
};

}
