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
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
    _cameraSystem(scene.system<CameraSystem>()),
    _debugSystem(scene.system<DebugSystem>()),
    _inputSystem(scene.system<InputSystem>()),
    _shipControlSystem(scene.system<ShipControlSystem>())
{
    _keyboard.registerListener(*this);
    _mouse.setMode(MouseMode::Relative);
}

void PlayerInputSystem::tick(double timeStep)
{
    if (_cameraSystem)
    {
        Camera::Iterator camera = _cameraSystem->activeCamera();
        if (camera)
        {
            if (_inputSystem)
            {
                double exposure = _inputSystem->axisValue("exposure");
                camera->exposure += exposure * 5.0 * timeStep;
                camera->exposure = std::max(0.01, camera->exposure);
            }
        }
    }

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

void PlayerInputSystem::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType::KeyDown)
    {
        if (event.key == Key::Tab)
        {
            MouseMode mode = _mouse.mode();
            if (mode == MouseMode::Cursor)
            {
                _mouse.setMode(MouseMode::Relative);
            }
            else
            {
                _mouse.setMode(MouseMode::Cursor);
            }
        }
        else if (event.key == Key::F1)
        {
            if (_debugSystem)
            {
                _debugSystem->toggleShowInterface();
            }
        }
        else if (event.key == Key::Esc)
        {
            scene().setActive(false);
        }
    }
}