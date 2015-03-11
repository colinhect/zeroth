///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include "Components/PlayerShipControl.h"
#include "Components/ObserverCamera.h"
#include "Systems/ObserverCameraSystem.h"

using namespace zeroth;

PlayerShipControlSystem::PlayerShipControlSystem(Engine& engine, Scene& scene) :
    ShipControlSystem(engine, scene)
{
}

void PlayerShipControlSystem::tick(double timeStep)
{
    // If there is no observer camera
    auto observerCamera = scene().components<ObserverCamera>().begin();
    if (!observerCamera)
    {
        auto inputSystem = scene().system<InputSystem>();
        assert(inputSystem);

        double pitch = inputSystem->axisValue("pitch");
        double yaw = inputSystem->axisValue("yaw");
        double roll = inputSystem->axisValue("roll");
        double thrust = inputSystem->axisValue("thrustFront");

        for (auto& playerShipControl : scene().components<PlayerShipControl>())
        {
            auto entity = playerShipControl.entity();

            Vector3 angularAxis(pitch, roll, yaw);
            controlShip(*entity, angularAxis, thrust, timeStep);
        }
    }
}