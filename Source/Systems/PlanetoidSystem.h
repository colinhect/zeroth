///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/Planetoid.h"
#include "Components/PlanetoidPatch.h"

namespace zeroth
{

/// \system
class PlanetoidSystem :
    public System<PlanetoidSystem, Components<Planetoid>>
{
public:
    PlanetoidSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void onComponentAdded(Planetoid::Iterator planetoid) override;

private:
    void split(PlanetoidPatch::Iterator patch);

    Entity::Iterator createRootPatch(Planetoid::Iterator planetoid, CubeSide cubeSide);
    Mesh::Handle buildPatchMesh(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator patch, const Vector3& relativePosition);

    static Vector3 morphPointToSphere(const Vector3& point, const Vector3& relativePosition, double radius);
    static Vector3 projectUnitCubeToSphere(const Vector3& point);

    static const Vector3& cubeSideUpVector(CubeSide cubeSide);
    static const Vector3& cubeSideRightVector(CubeSide cubeSide);

    BoundingBoxSystem::Handle _boundingBoxSystem;
    CameraSystem::Handle _cameraSystem;
};

}