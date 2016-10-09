///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalacticScene.h"

#include "Systems/GalaxySystem.h"

using namespace zeroth;

GalacticScene::GalacticScene(Engine& engine) :
    Scene(engine),
    _galaxySystem(createSystem<GalaxySystem>()),
    _galacticCameraEntity(createEntity("GalacticCamera")->createHandle())
{
    _galacticCameraComponent = _galacticCameraEntity->addComponent<CameraComponent>();
}

void GalacticScene::updateCamera(const CameraComponent& camera)
{
    if (_galacticCameraEntity && _galacticCameraComponent)
    {
        Vector3 position = _galacticCameraComponent->position;
        _galacticCameraComponent = _galacticCameraEntity->replaceComponent<CameraComponent>(camera);
        _galacticCameraComponent->position = position;
    }
}

Vector3 GalacticScene::observerPosition() const
{
    Vector3 position;
    if (_galacticCameraEntity && _galacticCameraComponent)
    {
        position = _galacticCameraComponent->position;
    }
    return position;
}

void GalacticScene::setObserverPosition(const Vector3& position)
{
    if (_galacticCameraEntity && _galacticCameraComponent)
    {
        _galacticCameraComponent->position = position;
    }
}

void GalacticScene::tick(double timeStep)
{
    Scene::refresh();

    _transformSystem->updateCommittedTransforms();
    _cameraSystem->updateAllCameras();
    _galaxySystem->adaptGalaxyNodes();

    Scene::refresh();
}

void GalacticScene::render(RenderTarget& target)
{
    throw InvalidOperation("Galactic scene can not be directly rendered");
}

