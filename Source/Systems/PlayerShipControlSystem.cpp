///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include "Components/PlayerShipControl.h"

PlayerShipControlSystem::PlayerShipControlSystem(Scene& scene, PhysicsSystem& physicsSystem, InputSystem& inputSystem) :
    ShipControlSystem(scene, physicsSystem),
    _inputSystem(&inputSystem),
    _thrust(nullptr),
    _yaw(nullptr),
    _yawLeft(nullptr),
    _yawRight(nullptr),
    _pitch(nullptr),
    _roll(nullptr),
    _rollLeft(nullptr),
    _rollRight(nullptr)
{
    if (inputSystem.hasAxisWithName("thrust"))
    {
        _thrust = &inputSystem.axisWithName("thrust");
    }

    if (inputSystem.hasAxisWithName("yaw"))
    {
        _yaw = &inputSystem.axisWithName("yaw");
    }

    if (inputSystem.hasAxisWithName("yawLeft"))
    {
        _yawLeft = &inputSystem.axisWithName("yawLeft");
    }

    if (inputSystem.hasAxisWithName("yawRight"))
    {
        _yawRight = &inputSystem.axisWithName("yawRight");
    }

    if (inputSystem.hasAxisWithName("pitch"))
    {
        _pitch = &inputSystem.axisWithName("pitch");
    }

    if (inputSystem.hasAxisWithName("roll"))
    {
        _roll = &inputSystem.axisWithName("roll");
    }

    if (inputSystem.hasAxisWithName("rollLeft"))
    {
        _rollLeft = &inputSystem.axisWithName("rollLeft");
    }

    if (inputSystem.hasAxisWithName("rollRight"))
    {
        _rollRight = &inputSystem.axisWithName("rollRight");
    }
}

void PlayerShipControlSystem::update(Real timeStep)
{
    for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
    {
        Entity& entity = playerShipControl.entity();

        Real pitch = 0;
        if (_pitch)
        {
            pitch = _pitch->value();
        }
        
        Real yaw = 0;
        if (_yaw)
        {
            yaw = _yaw->value();
        }
        if (_yawLeft)
        {
            yaw -= (_yawLeft->value() + 1) * 0.5;
        }
        if (_yawRight)
        {
            yaw += (_yawRight->value() + 1) * 0.5;
        }

        Real roll = 0;
        if (_roll)
        {
            roll = _roll->value();
        }
        if (_rollLeft)
        {
            roll -= (_rollLeft->value() + 1) * 0.5;
        }
        if (_rollRight)
        {
            roll += (_rollRight->value() + 1) * 0.5;
        }

        Real thrust = 0;
        if (_thrust)
        {
            thrust = _thrust->value();

            Real totalThrust = std::abs(thrust);
            if (totalThrust > 0.1)
            {
                size_t joystickIndex = _thrust->joystickIndex();
                Joystick& joystick = _inputSystem->joystick(joystickIndex);
                joystick.hapticRumble(totalThrust, TimeSpan::fromSeconds(timeStep));
            }
        }

        Vector3 angularAxis(pitch, yaw, roll);
        controlShip(entity, angularAxis, thrust, timeStep);
    }
}