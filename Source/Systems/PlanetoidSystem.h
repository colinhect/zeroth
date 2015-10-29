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
    Entity::Iterator createPatch(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator parentPatch, const Vector3& localPosition, double size, const Vector3& up, const Vector3& right);
    Mesh::Handle buildPatchMesh(PlanetoidPatch::Iterator patch, const Vector3& up, const Vector3& right);

    BoundingBoxSystem::Handle _boundingBoxSystem;
    CameraSystem::Handle _cameraSystem;
};

}