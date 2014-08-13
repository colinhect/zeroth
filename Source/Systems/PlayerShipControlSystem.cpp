///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Logic/Scene.h>

#include "Components/PlayerShipControl.h"

PlayerShipControlSystem::PlayerShipControlSystem(Scene& scene) :
    ShipControlSystem(scene)
{
}

void PlayerShipControlSystem::update()
{
    Real timeStep = scene().timeStep().seconds();
    InputSystem& inputSystem = scene().system<InputSystem>();

    for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
    {
        Entity& entity = playerShipControl.entity();

        Real pitch = inputSystem.axisValue("pitch");

        Real yaw = 0;
        yaw -= (inputSystem.axisValue("yawLeft") + 1) * 0.5;
        yaw += (inputSystem.axisValue("yawRight") + 1) * 0.5;

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