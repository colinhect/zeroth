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
    System(engine, scene)
{
}

void CockpitCameraSystem::tick(double timeStep)
{
    (void)timeStep;

    CameraSystem& cameraSystem = scene().system<CameraSystem>();
    auto camera = cameraSystem.activeCamera();
    if (camera)
    {
        InputSystem& inputSystem = scene().system<InputSystem>();

        double exposure = inputSystem.axisValue("exposure");
        camera->exposure = (1 - exposure) * 0.2 + exposure * 10.0;
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

                double rotateSpeed = timeStep * 1;

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