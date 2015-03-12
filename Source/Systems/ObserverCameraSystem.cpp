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
    System(engine, scene),
    _cameraSystem(scene.system<CameraSystem>()),
    _transformSystem(scene.system<TransformSystem>()),
    _inputSystem(scene.system<InputSystem>())
{
    _observerEntity = scene.createEntity("Test/Observer.entity");

    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.registerListener(*this);

    Mouse& mouse = engine.platform().mouse();
    mouse.registerListener(*this);
}

void ObserverCameraSystem::tick(double timeStep)
{
    if (_inputSystem && _transformSystem)
    {
        for (ObserverCamera& observerCamera : scene().components<ObserverCamera>())
        {
            Entity::Iterator entity = observerCamera.entity();

            double lookSpeed = timeStep * observerCamera.lookSpeed;
            double rollSpeed = timeStep * observerCamera.rollSpeed;
            double moveSpeed = timeStep * observerCamera.moveSpeed;

            Transform::Iterator transform = entity->component<Transform>();
            Camera::Iterator camera = entity->component<Camera>();
            if (transform && camera)
            {
                transform->localRotation *= Quaternion::fromAxisAngle(camera->up, _inputSystem->axisValue("yaw") * -lookSpeed);
                transform->localRotation *= Quaternion::fromAxisAngle(camera->right, _inputSystem->axisValue("pitch") * lookSpeed);
                transform->localRotation *= Quaternion::fromAxisAngle(camera->front, _inputSystem->axisValue("roll") * -rollSpeed);

                transform->localPosition += camera->front * _inputSystem->axisValue("thrustFront") * moveSpeed;
                transform->localPosition += camera->right * _inputSystem->axisValue("thrustRight") * moveSpeed;

                _transformSystem->commit(*transform);
            }
        }
    }
}

void ObserverCameraSystem::receiveEvent(const KeyboardEvent& event)
{
    if (_cameraSystem && _transformSystem)
    {
        if (event.type == KeyboardEventType_KeyDown && event.key == Key_F)
        {
            if (_activeObserver)
            {
                // Restore the last active camera
                if (_lastActiveCamera)
                {
                    Camera::Iterator camera = _lastActiveCamera->component<Camera>();
                    if (camera)
                    {
                        // Preserve the exposure of the last observer camera
                        Camera::Iterator observerCamera = _activeObserver->component<Camera>();
                        if (observerCamera)
                        {
                            camera->exposure = observerCamera->exposure;
                        }

                        _cameraSystem->setActiveCamera(*camera);
                    }

                    _lastActiveCamera = Entity::Handle();
                }

                _activeObserver->destroy();
            }
            else
            {
                // Remember the active camera
                Camera::Iterator camera = _cameraSystem->activeCamera();
                if (camera)
                {
                    _lastActiveCamera = camera->entity()->createHandle();
                }

                // Instantiate an observer
                Entity::Iterator observer = _observerEntity->clone();
                observer->activate();

                if (_lastActiveCamera)
                {
                    // Preserve the exposure of the last active camera
                    Camera::Iterator camera = _lastActiveCamera->component<Camera>();
                    if (camera)
                    {
                        Camera::Iterator observerCamera = observer->component<Camera>();
                        if (observerCamera)
                        {
                            observerCamera->exposure = camera->exposure;
                        }
                    }

                    // Preserve the transform of the last active camera
                    Transform::Iterator transform = _lastActiveCamera->component<Transform>();
                    if (transform)
                    {
                        Transform::Iterator observerTransform = observer->component<Transform>();
                        if (observerTransform)
                        {
                            observerTransform->localPosition = transform->globalPosition;
                            observerTransform->localRotation = transform->globalRotation;
                            _transformSystem->update(*observerTransform);
                        }
                    }
                }

                // Set as active observer
                _activeObserver = observer->createHandle();

                // Set active camera
                Camera::Iterator observerCamera = _activeObserver->component<Camera>();
                if (observerCamera)
                {
                    _cameraSystem->setActiveCamera(*observerCamera);
                }
            }
        }
    }
}

void ObserverCameraSystem::receiveEvent(const MouseEvent& event)
{
    if (event.type == MouseEventType_ScrollUp)
    {
        for (ObserverCamera& observerCamera : scene().components<ObserverCamera>())
        {
            observerCamera.moveSpeed *= 2;
            HECT_DEBUG(format("moveSpeed = %f", observerCamera.moveSpeed));
        }
    }
    else if (event.type == MouseEventType_ScrollDown)
    {
        for (ObserverCamera& observerCamera : scene().components<ObserverCamera>())
        {
            observerCamera.moveSpeed /= 2;
            HECT_DEBUG(format("moveSpeed = %f", observerCamera.moveSpeed));
        }
    }
}