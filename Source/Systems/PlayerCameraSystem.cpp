///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerCameraSystem.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Spacial/Components/Transform.h>

#include "Components/PlayerCamera.h"

PlayerCameraSystem::PlayerCameraSystem(Scene& scene) :
    System(scene),
    _speed(16)
{
}

void PlayerCameraSystem::update()
{
    Real timeStep = scene().timeStep().seconds();

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

                /*
                if (_inputDevices->mouse().mode() == MouseMode_Relative)
                {
                    if (_viewX)
                    {
                        transform->rotate(up, _viewX->value() * rotateSpeed);
                    }

                    if (_viewY)
                    {
                        transform->rotate(right, _viewY->value() * -rotateSpeed);
                    }

                    if (_roll)
                    {
                        transform->rotate(front, _roll->value() * -rollSpeed);
                    }
                }

                if (_moveX)
                {
                    transform->translate(right * _moveX->value() * moveSpeed);
                }

                if (_moveY)
                {
                    transform->translate(front * _moveY->value() * moveSpeed);
                }
                */
            }
        }
    }
}