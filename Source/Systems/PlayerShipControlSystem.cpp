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
    _thrust(&inputSystem.axisWithName("thrust")),
    _yaw(&inputSystem.axisWithName("yaw")),
    _pitch(&inputSystem.axisWithName("pitch")),
    _roll(&inputSystem.axisWithName("roll"))
{
}

PlayerShipControlSystem::~PlayerShipControlSystem()
{
}

void PlayerShipControlSystem::update(Real timeStep)
{
    for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
    {
        Entity& entity = playerShipControl.entity();

        Vector3 angularAxis(_pitch->value(), _yaw->value(), _roll->value());

        controlShip(entity, angularAxis, _thrust->value(), timeStep);
    }
}