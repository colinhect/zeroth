///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

#include "Components/PlayerShipControl.h"
#include "Components/ObserverCamera.h"
#include "Systems/ObserverCameraSystem.h"
#include "Systems/ShipControlSystem.h"

using namespace zeroth;

PlayerInputSystem::PlayerInputSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void PlayerInputSystem::tick(double timeStep)
{
    // If there is no observer camera
    auto observerCamera = scene().components<ObserverCamera>().begin();
    if (!observerCamera)
    {
        auto shipControlSystem = scene().system<ShipControlSystem>();
        assert(shipControlSystem);

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
            shipControlSystem->controlShip(*entity, angularAxis, thrust, timeStep);
        }
    }
}