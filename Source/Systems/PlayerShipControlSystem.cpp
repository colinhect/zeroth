///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include <Hect/Logic/World.h>
#include <Hect/Logic/Systems/BoundingBoxSystem.h>
#include <Hect/Logic/Systems/InputSystem.h>

#include "Components/PlayerShipControl.h"
#include "Systems/PlayerCameraSystem.h"

using namespace zeroth;

PlayerShipControlSystem::PlayerShipControlSystem(World& world) :
    ShipControlSystem(world)
{
    tickAfter<BoundingBoxSystem>();
}

void PlayerShipControlSystem::tick(Real timeStep)
{
    InputSystem& inputSystem = world().system<InputSystem>();

    for (PlayerShipControl& playerShipControl : world().components<PlayerShipControl>())
    {
        Entity& entity = playerShipControl.entity();

        Real pitch = inputSystem.axisValue("pitch");
        Real yaw = inputSystem.axisValue("yaw");
        Real roll = inputSystem.axisValue("roll");
        Real thrust = inputSystem.axisValue("thrust");

        Real totalThrust = std::abs(thrust);
        if (totalThrust > 0.1)
        {
            //size_t joystickIndex = _thrust->joystickIndex();
            //Joystick& joystick = ->joystick(joystickIndex);
            //joystick.hapticRumble(totalThrust, TimeSpan::fromSeconds(timeStep));
        }

        Vector3 angularAxis(pitch, yaw, roll);
        controlShip(entity, angularAxis, thrust, timeStep);
    }
}