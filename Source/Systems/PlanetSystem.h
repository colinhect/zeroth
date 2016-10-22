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
#include "Components/PlanetComponent.h"
#include "Components/PlanetPatchComponent.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT PlanetSystem :
    public System<PlanetSystem, Components<PlanetComponent>>
{
public:
    PlanetSystem(Engine& engine, Scene& scene);

    void adaptPlanets();

private:
    void adapt(Entity::Iterator entity, Vector3 cameraPosition);

    void split(PlanetPatchComponent::Iterator patch);
    void join(PlanetPatchComponent::Iterator patch);

    void createPlanet(PlanetComponent::Iterator planet);

    Entity::Iterator createPatch(Entity::Iterator parent, CubeSide cubeSide, Vector3 localPosition, Vector3 parentGlobalPosition);
    Entity::Iterator createRootPatch(PlanetComponent::Iterator planet, CubeSide cubeSide);

    Mesh::Handle buildPatchMesh(PlanetComponent::Iterator planet, PlanetPatchComponent::Iterator patch, Vector3 localPosition, Vector3 parentGlobalPosition);

    // System overrides
    void onComponentAdded(PlanetComponent::Iterator planet) override;

    static Vector3 morphPointToSphere(Vector3 point, Vector3 localPosition, double radius);
    static Vector3 projectUnitCubeToSphere(Vector3 point);

    static Vector3 cubeSideUpVector(CubeSide cubeSide);
    static Vector3 cubeSideRightVector(CubeSide cubeSide);

    AssetCache& _assetCache;

    PlanetComponent::Iterator _planet;
};

}
