///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerCameraSystem.h"

#include <Hect/Logic/World.h>
#include <Hect/Logic/Components/Camera.h>
#include <Hect/Logic/Components/Transform.h>
#include <Hect/Logic/Systems/InputSystem.h>

#include "Components/PlayerCamera.h"
#include "Systems/CockpitCameraSystem.h"

using namespace zeroth;

PlayerCameraSystem::PlayerCameraSystem(World& world) :
    System(world),
    _speed(16)
{
    tickAfter<CockpitCameraSystem>();
}

void PlayerCameraSystem::tick(Real timeStep)
{

    for (PlayerCamera& playerCamera : world().components<PlayerCamera>())
    {
        Entity& entity = playerCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                const Vector3& up = camera->up;
                const Vector3& right = camera->right;
                const Vector3& front = camera->front;

                Real rotateSpeed = timeStep * 50;
                Real rollSpeed = timeStep * 2;
                Real moveSpeed = timeStep * _speed;

                /*
                if (->mouse().mode() == MouseMode_Relative)
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