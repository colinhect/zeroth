///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ObserverCameraSystem.h"

#include "Components/ObserverCamera.h"

using namespace zeroth;

ObserverCameraSystem::ObserverCameraSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
    _observerEntity = scene.createEntity("Test/Observer.entity");

    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.addListener(*this);
}

void ObserverCameraSystem::tick(double timeStep)
{
    InputSystem& inputSystem = scene().system<InputSystem>();
    TransformSystem& transformSystem = scene().system<TransformSystem>();

    for (ObserverCamera& observerCamera : scene().components<ObserverCamera>())
    {
        Entity& entity = *observerCamera.entity();

        double lookSpeed = timeStep * observerCamera.lookSpeed;
        double rollSpeed = timeStep * observerCamera.rollSpeed;
        double moveSpeed = timeStep * observerCamera.moveSpeed;

        auto transform = entity.component<Transform>();
        auto camera = entity.component<Camera>();
        if (transform && camera)
        {
            transform->localRotation *= Quaternion::fromAxisAngle(camera->up, inputSystem.axisValue("yaw") * -lookSpeed);
            transform->localRotation *= Quaternion::fromAxisAngle(camera->right, inputSystem.axisValue("pitch") * lookSpeed);
            transform->localRotation *= Quaternion::fromAxisAngle(camera->front, inputSystem.axisValue("roll") * -rollSpeed);

            transform->localPosition += camera->front * inputSystem.axisValue("thrust") * moveSpeed;

            transformSystem.commit(*transform);
        }
    }
}

void ObserverCameraSystem::receiveEvent(const KeyboardEvent& event)
{
    CameraSystem& cameraSystem = scene().system<CameraSystem>();
    TransformSystem& transformSystem = scene().system<TransformSystem>();

    if (event.type == KeyboardEventType_KeyDown && event.key == Key_F)
    {
        if (_activeObserver)
        {
            // Restore the last active camera
            if (_lastActiveCamera)
            {
                auto camera = _lastActiveCamera->component<Camera>();
                if (camera)
                {
                    cameraSystem.setActiveCamera(*camera);
                }

                _lastActiveCamera = Entity::Handle();
            }

            _activeObserver->destroy();
        }
        else
        {
            // Remember the active camera
            auto camera = cameraSystem.activeCamera();
            if (camera)
            {
                _lastActiveCamera = camera->entity()->createHandle();
            }

            // Instantiate an observer
            auto observer = _observerEntity->clone();
            observer->activate();

            if (_lastActiveCamera)
            {
                auto transform = _lastActiveCamera->component<Transform>();
                if (transform)
                {
                    auto observerTransform = observer->component<Transform>();
                    if (observerTransform)
                    {
                        observerTransform->localPosition = transform->globalPosition;
                        observerTransform->localRotation = transform->globalRotation;
                        transformSystem.update(*observerTransform);
                    }
                }
            }

            // Set as active observer
            _activeObserver = observer->createHandle();

            // Set active camera
            auto observerCamera = _activeObserver->component<Camera>();
            if (observerCamera)
            {
                cameraSystem.setActiveCamera(*observerCamera);
            }
        }
    }
}