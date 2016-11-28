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
    _boundingBoxSystem(createSystem<BoundingBoxSystem>()),
    _cameraSystem(createSystem<CameraSystem>()),
    _transformSystem(createSystem<TransformSystem>()),
    _galaxySystem(createSystem<GalaxySystem>())
{
}

void GalacticScene::spawnGalaxy()
{
    if (_galaxyEntity)
    {
        _galaxyEntity->destroy();
    }

    _galaxyEntity = createEntity("Galaxy")->createHandle();
    _galaxyEntity->addComponent<SpiralGalaxyComponent>();
    _galaxyEntity->activate();
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

void GalacticScene::initialize()
{
    Scene::initialize();

    _galacticCameraEntity = createEntity("GalacticCamera")->createHandle();
    _galacticCameraComponent = _galacticCameraEntity->addComponent<CameraComponent>();
    _galacticCameraEntity->activate();
}

void GalacticScene::tick(double timeStep)
{
    Scene::refresh();

    _transformSystem.updateCommittedTransforms();
    _cameraSystem.updateAllCameras();
    _galaxySystem.adaptGalaxyNodes();

    Scene::refresh();
}

void GalacticScene::render(RenderTarget& target)
{
    throw InvalidOperation("Galactic scene can not be directly rendered");
}

