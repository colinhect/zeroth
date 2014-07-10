///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerCameraSystem.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Spacial/Components/Transform.h>

PlayerCameraSystem::PlayerCameraSystem(Scene& scene, InputSystem& inputSystem) :
    System(scene),
    _mouse(&inputSystem.mouse()),
    _viewX(&inputSystem.axisWithName("viewX")),
    _viewY(&inputSystem.axisWithName("viewY")),
    _moveX(&inputSystem.axisWithName("moveX")),
    _moveY(&inputSystem.axisWithName("moveY")),
    _roll(&inputSystem.axisWithName("roll")),
    _speed(16)
{
}

void PlayerCameraSystem::update(Real timeStep)
{
    for (PlayerCamera& playerCamera : scene().components<PlayerCamera>())
    {
        Entity& entity = playerCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                const Vector3& up = camera->up();
                const Vector3& right = camera->right();
                const Vector3& front = camera->front();

                Real rotateSpeed = timeStep * 50;
                Real rollSpeed = timeStep * 2;
                Real moveSpeed = timeStep * _speed;

                if (_mouse->mode() == MouseMode_Relative)
                {
                    transform->rotate(up, _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                    transform->rotate(front, _roll->value() * -rollSpeed);
                }

                transform->translate(right * _moveX->value() * moveSpeed);
                transform->translate(front * _moveY->value() * moveSpeed);
            }
        }
    }
}