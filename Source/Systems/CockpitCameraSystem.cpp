///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "CockpitCameraSystem.h"

#include "Components/CockpitCamera.h"

using namespace zeroth;

CockpitCameraSystem::CockpitCameraSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void CockpitCameraSystem::tick(double timeStep)
{
    (void)timeStep;

    /*
    for (CockpitCamera& cockpitCamera : scene().components<CockpitCamera>())
    {
        Entity& entity = cockpitCamera.entity();

        Transform::Iterator transform = entity.component<Transform>();
        if (transform)
        {
            Camera::Iterator camera = entity.component<Camera>();
            if (camera)
            {
                Vector3 up = camera->up;
                Vector3 right = camera->right;

                double rotateSpeed = timeStep * 1;

                if (->mouse().mode() == MouseMode::Relative && _viewX && _viewY)
                {
                    transform->rotate(Vector3::UnitY, _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                }
            }
        }
    }
    */
}