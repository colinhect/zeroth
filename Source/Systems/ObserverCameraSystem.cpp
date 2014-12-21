///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ObserverCameraSystem.h"

#include "Components/ObserverCamera.h"

using namespace zeroth;

ObserverCameraSystem::ObserverCameraSystem(Scene& scene) :
    System(scene)
{
}

void ObserverCameraSystem::tick(Real timeStep)
{
    InputSystem& inputSystem = scene().system<InputSystem>();
    TransformSystem& transformSystem = scene().system<TransformSystem>();

    for (ObserverCamera& observerCamera : scene().components<ObserverCamera>())
    {
        Entity& entity = observerCamera.entity();

        Real rotateSpeed = timeStep * observerCamera.rotateSpeed;
        Real moveSpeed = timeStep * observerCamera.moveSpeed;

        auto transform = entity.component<Transform>();
        auto camera = entity.component<Camera>();
        if (transform && camera)
        {
            transform->localRotation *= Quaternion::fromAxisAngle(camera->up, inputSystem.axisValue("yaw") * -rotateSpeed);
            transform->localRotation.normalize();
            transform->localRotation *= Quaternion::fromAxisAngle(camera->right, inputSystem.axisValue("pitch") * rotateSpeed);
            transform->localRotation.normalize();
            transform->localRotation *= Quaternion::fromAxisAngle(camera->front, inputSystem.axisValue("roll") * -rotateSpeed);
            transform->localRotation.normalize();

            transform->localPosition += camera->front * inputSystem.axisValue("thrust") * moveSpeed;

            transformSystem.markForUpdate(*transform);
        }
    }
}