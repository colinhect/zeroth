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

#include "Systems/GalaxySystem.h"
#include "Systems/ObserverCameraSystem.h"

namespace zeroth
{

/// \scene
class ZEROTH_EXPORT GalacticScene :
    public Scene
{
public:
    GalacticScene(Engine& engine);

    void spawnGalaxy();

    // TODO: Star query interface for the master scene to use when spawning in
    // the systemic/celestial scenes

    // TODO: Change RenderSystem to work on any scene (state-less) and let
    // ZerothScene just render the GalacticScene first.

    // Updates the camera's properties and orientations
    void updateCamera(const CameraComponent& camera);

    Vector3 observerPosition() const;
    void setObserverPosition(const Vector3& position);

    // Scene overrides
    virtual void initialize() override;
    virtual void tick(double timeStep) override;
    virtual void render(RenderTarget& target) override;

private:
    BoundingBoxSystem& _boundingBoxSystem;
    CameraSystem& _cameraSystem;
    TransformSystem& _transformSystem;
    GalaxySystem& _galaxySystem;

    Entity::Handle _galaxyEntity;

    // The camera from which the galactic scene is rendered
    Entity::Handle _galacticCameraEntity;
    CameraComponent::Iterator _galacticCameraComponent;
};

}
