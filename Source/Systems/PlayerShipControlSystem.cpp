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

void PlayerShipControlSystem::tick(Real timeStep)
{
    InputSystem& inputSystem = scene().system<InputSystem>();

    for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
    {
        Entity& entity = *playerShipControl.entity();

        Real pitch = inputSystem.axisValue("pitch");
        Real yaw = inputSystem.axisValue("yaw");
        Real roll = inputSystem.axisValue("roll");
        Real thrust = inputSystem.axisValue("thrust");

        Vector3 angularAxis(pitch, yaw, roll);
        controlShip(entity, angularAxis, thrust, timeStep);
    }
}