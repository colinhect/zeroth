///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

#include "Components/PlayerShipControl.h"
#include "Components/ObserverCamera.h"

using namespace zeroth;

PlayerInputSystem::PlayerInputSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _inputSystem(scene.system<InputSystem>()),
    _shipControlSystem(scene.system<ShipControlSystem>())
{
}

void PlayerInputSystem::tick(double timeStep)
{
    if (_inputSystem && _shipControlSystem)
    {
        // If there is no observer camera
        ObserverCamera::Iterator observerCamera = scene().components<ObserverCamera>().begin();
        if (!observerCamera)
        {
            double pitch = _inputSystem->axisValue("pitch");
            double yaw = _inputSystem->axisValue("yaw");
            double roll = _inputSystem->axisValue("roll");
            double thrust = _inputSystem->axisValue("thrustFront");

            for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
            {
                Entity::Iterator entity = playerShipControl.entity();

                Vector3 angularAxis(pitch, roll, yaw);
                _shipControlSystem->controlShip(*entity, angularAxis, thrust, timeStep);
            }
        }
    }
}