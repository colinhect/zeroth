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
    Entity::Iterator createRootPatch(Planetoid::Iterator planetoid, const Vector3& up, const Vector3& right);
    Mesh::Handle buildPatchMesh(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator patch, const Vector3& relativePosition, const Vector3& up, const Vector3& right);

    static Vector3 cubeToSphere(const Vector3& point);

    BoundingBoxSystem::Handle _boundingBoxSystem;
    CameraSystem::Handle _cameraSystem;
};

}