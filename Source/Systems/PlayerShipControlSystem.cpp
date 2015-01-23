///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include "Components/PlayerShipControl.h"
#include "Systems/ObserverCameraSystem.h"

using namespace zeroth;

PlayerShipControlSystem::PlayerShipControlSystem(Engine& engine, Scene& scene) :
    ShipControlSystem(engine, scene)
{
}

void PlayerShipControlSystem::tick(double timeStep)
{
    InputSystem& inputSystem = scene().system<InputSystem>();

    for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
    {
        Entity& entity = *playerShipControl.entity();

        double pitch = inputSystem.axisValue("pitch");
        double yaw = inputSystem.axisValue("yaw");
        double roll = inputSystem.axisValue("roll");
        double thrust = inputSystem.axisValue("thrust");

        Vector3 angularAxis(pitch, roll, yaw);
        controlShip(entity, angularAxis, thrust, timeStep);
    }
}