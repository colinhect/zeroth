///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerShipControlSystem.h"

#include "Components/PlayerShipControl.h"

PlayerShipControlSystem::PlayerShipControlSystem(Scene& scene, PhysicsSystem& physicsSystem, Input& input) :
    ShipControlSystem(scene, physicsSystem),
    _input(&input),
    _thrust(nullptr),
    _yaw(nullptr),
    _yawLeft(nullptr),
    _yawRight(nullptr),
    _pitch(nullptr),
    _roll(nullptr),
    _rollLeft(nullptr),
    _rollRight(nullptr)
{
    if (input.axisExists("thrust"))
    {
        _thrust = &input.axis("thrust");
    }

    if (input.axisExists("yaw"))
    {
        _yaw = &input.axis("yaw");
    }

    if (input.axisExists("yawLeft"))
    {
        _yawLeft = &input.axis("yawLeft");
    }

    if (input.axisExists("yawRight"))
    {
        _yawRight = &input.axis("yawRight");
    }

    if (input.axisExists("pitch"))
    {
        _pitch = &input.axis("pitch");
    }

    if (input.axisExists("roll"))
    {
        _roll = &input.axis("roll");
    }

    if (input.axisExists("rollLeft"))
    {
        _rollLeft = &input.axis("rollLeft");
    }

    if (input.axisExists("rollRight"))
    {
        _rollRight = &input.axis("rollRight");
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
                Joystick& joystick = _input->joystick(joystickIndex);
                joystick.hapticRumble(totalThrust, TimeSpan::fromSeconds(timeStep));
            }
        }

        Vector3 angularAxis(pitch, yaw, roll);
        controlShip(entity, angularAxis, thrust, timeStep);
    }
}