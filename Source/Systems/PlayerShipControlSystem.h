///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Input/InputSystem.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Logic/System.h>

#include "Components/PlayerShipControl.h"
#include "Systems/ShipControlSystem.h"

using namespace hect;

class PlayerShipControlSystem :
    public ShipControlSystem
{
public:
    PlayerShipControlSystem(Scene& scene, PhysicsSystem& physicsSystem, InputSystem& inputSystem);

    void update(Real timeStep);

private:
    InputSystem* _inputSystem;

    const InputAxis* _thrust;
    const InputAxis* _yaw;
    const InputAxis* _yawLeft;
    const InputAxis* _yawRight;
    const InputAxis* _pitch;
    const InputAxis* _roll;
    const InputAxis* _rollLeft;
    const InputAxis* _rollRight;
};