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

    /// \property
    Material::Handle patchMaterial;

    /// \property
    unsigned patchResolution { 16 };

private:
    Entity::Iterator createPatch(Planetoid::Iterator planetoid, double size, const Vector3& localPosition, const Vector3& parentGlobalPosition);

    CameraSystem::Handle _cameraSystem;
};

}