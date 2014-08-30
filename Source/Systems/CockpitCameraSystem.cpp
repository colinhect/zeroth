///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "CockpitCameraSystem.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Logic/World.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>
#include <Hect/Spacial/Components/Transform.h>

#include "Components/CockpitCamera.h"

CockpitCameraSystem::CockpitCameraSystem(World& world) :
    System(world)
{
    tickAfter<PhysicsSystem>();
}

void CockpitCameraSystem::tick(Real timeStep)
{
    for (CockpitCamera& cockpitCamera : world().components<CockpitCamera>())
    {
        Entity& entity = cockpitCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                const Vector3& up = camera->up();
                const Vector3& right = camera->right();

                Real rotateSpeed = timeStep * 1;

                /*
                if (->mouse().mode() == MouseMode_Relative && _viewX && _viewY)
                {
                    transform->rotate(Vector3::unitY(), _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                }
                */
            }
        }
    }
}