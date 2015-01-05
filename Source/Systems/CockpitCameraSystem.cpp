///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "CockpitCameraSystem.h"

#include "Components/CockpitCamera.h"

using namespace zeroth;

CockpitCameraSystem::CockpitCameraSystem(Engine& engine, Scene& scene) :
    System(scene)
{
    (void)engine;
}

void CockpitCameraSystem::tick(Real timeStep)
{
    CameraSystem& cameraSystem = scene().system<CameraSystem>();
    auto camera = cameraSystem.activeCamera();
    if (camera)
    {
        InputSystem& inputSystem = scene().system<InputSystem>();

        Real exposure = inputSystem.axisValue("exposure");
        camera->exposure = interpolate(Real(0.2), Real(10), exposure);
    }

    /*
    for (CockpitCamera& cockpitCamera : scene().components<CockpitCamera>())
    {
        Entity& entity = cockpitCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                const Vector3& up = camera->up;
                const Vector3& right = camera->right;

                Real rotateSpeed = timeStep * 1;

                if (->mouse().mode() == MouseMode_Relative && _viewX && _viewY)
                {
                    transform->rotate(Vector3::unitY(), _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                }
            }
        }
    }
    */
}