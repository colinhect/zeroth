///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

#include "Components/PlayerShipControlComponent.h"
#include "Components/ObserverCameraComponent.h"

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

void PlayerInputSystem::handlePlayerInput(double timeStep)
{
    controlPlayerShips(timeStep);
    adjustCameraExposure(timeStep);
}

void PlayerInputSystem::controlPlayerShips(double timeStep)
{
    if (_inputSystem && _shipControlSystem)
    {
        // Get the angular thrust from input
        Vector3 angularThrust;
        angularThrust.x = _inputSystem->axisValue("pitch");
        angularThrust.y = _inputSystem->axisValue("roll");
        angularThrust.z = _inputSystem->axisValue("yaw");

        // Get the directional thrust from input
        Vector3 directionalThrust;
        directionalThrust.x = _inputSystem->axisValue("thrustX");
        directionalThrust.y = _inputSystem->axisValue("thrustY");
        directionalThrust.z = _inputSystem->axisValue("thrustZ");

        for (PlayerShipControlComponent& playerShipControl : scene().components<PlayerShipControlComponent>())
        {
            Entity::Iterator entity = playerShipControl.entity();
            _shipControlSystem->controlShip(*entity, directionalThrust, angularThrust, timeStep);
        }
    }
}

void PlayerInputSystem::adjustCameraExposure(double timeStep)
{
    if (_cameraSystem)
    {
        // Adjust the exposure of the active camera
        CameraComponent::Iterator camera = _cameraSystem->activeCamera();
        if (camera)
        {
            double exposure = _inputSystem->axisValue("exposure");
            if (exposure != 0.0)
            {
                camera->exposure += exposure * 5.0 * timeStep;
                camera->exposure = std::max(0.01, camera->exposure);
            }
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

void PlayerInputSystem::parseKeyboardShortcut(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType::KeyDown)
    {
        switch (event.key)
        {
        case Key::Tab:
            swapMouseMode();
            break;
        case Key::F1:
            toggleDebugInterface();
            break;
        case Key::Esc:
            deactivateScene();
            break;
        }
    }
}

void PlayerInputSystem::deactivateScene()
{
    scene().setActive(false);
}

void PlayerInputSystem::receiveEvent(const KeyboardEvent& event)
{
    parseKeyboardShortcut(event);
}
