///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ObserverCameraSystem.h"

#include "Components/ObserverCameraComponent.h"

using namespace zeroth;

ObserverCameraSystem::ObserverCameraSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
    _cameraSystem(scene.system<CameraSystem>()),
    _transformSystem(scene.system<TransformSystem>()),
    _inputSystem(scene.system<InputSystem>())
{
    _keyboard.registerListener(*this);
    _mouse.registerListener(*this);
}

void ObserverCameraSystem::tickObservers(double timeStep)
{
    if (_inputSystem && _transformSystem && _mouse.mode() == MouseMode::Relative)
    {
        for (ObserverCameraComponent& observerCamera : scene().components<ObserverCameraComponent>())
        {
            Entity::Iterator entity = observerCamera.entity();

            double lookSpeed = observerCamera.lookSpeed * timeStep;
            double rollSpeed = observerCamera.rollSpeed * timeStep;
            double moveSpeed = observerCamera.moveSpeed * timeStep;

            TransformComponent::Iterator transform = entity->component<TransformComponent>();
            CameraComponent::Iterator camera = entity->component<CameraComponent>();
            if (transform && camera)
            {
                transform->localRotation *= Quaternion::fromAxisAngle(camera->up, Radians(_inputSystem->axisValue("yaw") * -lookSpeed));
                transform->localRotation *= Quaternion::fromAxisAngle(camera->right, Radians(_inputSystem->axisValue("pitch") * lookSpeed));
                transform->localRotation *= Quaternion::fromAxisAngle(camera->front, Radians(_inputSystem->axisValue("roll") * -rollSpeed));

                transform->localPosition += camera->right * _inputSystem->axisValue("thrustX") * moveSpeed;
                transform->localPosition += camera->front * _inputSystem->axisValue("thrustY") * moveSpeed;
                transform->localPosition += camera->up * _inputSystem->axisValue("thrustZ") * moveSpeed;

                _transformSystem->commitTransform(*transform);
            }
        }
    }
}

void ObserverCameraSystem::initialize()
{
    if (!observerArchetype.empty())
    {
        _observerArchetype = scene().loadEntity(observerArchetype);
    }
}

void ObserverCameraSystem::receiveEvent(const KeyboardEvent& event)
{
    if (_cameraSystem && _transformSystem && _observerArchetype)
    {
        if (event.type == KeyboardEventType::KeyDown && event.key == Key::F)
        {
            if (_activeObserver)
            {
                // Restore the last active camera
                if (_lastActiveCamera)
                {
                    CameraComponent::Iterator camera = _lastActiveCamera->component<CameraComponent>();
                    if (camera)
                    {
                        // Preserve the exposure of the last observer camera
                        CameraComponent::Iterator observerCamera = _activeObserver->component<CameraComponent>();
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
                CameraComponent::Iterator camera = _cameraSystem->activeCamera();
                if (camera)
                {
                    _lastActiveCamera = camera->entity()->createHandle();
                }

                // Instantiate an observer
                Entity::Iterator observer = _observerArchetype->clone();
                observer->activate();

                if (_lastActiveCamera)
                {
                    // Preserve the exposure of the last active camera
                    CameraComponent::Iterator camera = _lastActiveCamera->component<CameraComponent>();
                    if (camera)
                    {
                        CameraComponent::Iterator observerCamera = observer->component<CameraComponent>();
                        if (observerCamera)
                        {
                            observerCamera->exposure = camera->exposure;
                        }
                    }

                    // Preserve the transform of the last active camera
                    TransformComponent::Iterator transform = _lastActiveCamera->component<TransformComponent>();
                    if (transform)
                    {
                        TransformComponent::Iterator observerTransform = observer->component<TransformComponent>();
                        if (observerTransform)
                        {
                            observerTransform->localPosition = transform->globalPosition;
                            observerTransform->localRotation = transform->globalRotation;
                            _transformSystem->updateTransform(*observerTransform);
                        }
                    }
                }

                // Set as active observer
                _activeObserver = observer->createHandle();

                // Set active camera
                CameraComponent::Iterator observerCamera = _activeObserver->component<CameraComponent>();
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
    if (event.type == MouseEventType::ScrollUp)
    {
        for (ObserverCameraComponent& observerCamera : scene().components<ObserverCameraComponent>())
        {
            observerCamera.moveSpeed *= 2;
            HECT_DEBUG(format("moveSpeed = %f", observerCamera.moveSpeed));
        }
    }
    else if (event.type == MouseEventType::ScrollDown)
    {
        for (ObserverCameraComponent& observerCamera : scene().components<ObserverCameraComponent>())
        {
            observerCamera.moveSpeed /= 2;
            HECT_DEBUG(format("moveSpeed = %f", observerCamera.moveSpeed));
        }
    }
}
