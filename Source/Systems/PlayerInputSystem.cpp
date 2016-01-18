///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
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
            Vector3 angularThrust;
            angularThrust.x = _inputSystem->axisValue("pitch");
            angularThrust.y = _inputSystem->axisValue("roll");
            angularThrust.z = _inputSystem->axisValue("yaw");

            Vector3 directionalThrust;
            directionalThrust.x = _inputSystem->axisValue("thrustX");
            directionalThrust.y = _inputSystem->axisValue("thrustY");
            directionalThrust.z = _inputSystem->axisValue("thrustZ");

            for (PlayerShipControl& playerShipControl : scene().components<PlayerShipControl>())
            {
                Entity::Iterator entity = playerShipControl.entity();

                _shipControlSystem->controlShip(*entity, directionalThrust, angularThrust, timeStep);
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
            swapMouseMode();
        }
        else if (event.key == Key::F1)
        {
            toggleDebugInterface();
        }
        else if (event.key == Key::Esc)
        {
            deactivateScene();
        }
    }
}

void PlayerInputSystem::swapMouseMode()
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

void PlayerInputSystem::toggleDebugInterface()
{
    if (_debugSystem)
    {
        _debugSystem->toggleShowInterface();
    }
}

void PlayerInputSystem::deactivateScene()
{
    scene().setActive(false);
}
