///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

using namespace zeroth;

PlayerInputSystem::PlayerInputSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse())
{
    _keyboard.registerListener(*this);
    _mouse.setMode(MouseMode::Relative);
}

void PlayerInputSystem::handlePlayerInput(Seconds timeStep)
{
    adjustCameraExposure(timeStep);
}

void PlayerInputSystem::adjustCameraExposure(Seconds timeStep)
{
    // Adjust the exposure of the active camera
    auto& cameraSystem = scene().system<CameraSystem>();
    CameraComponent::Iterator camera = cameraSystem.activeCamera();
    if (camera)
    {
        auto& inputSystem = scene().system<InputSystem>();
        double exposure = inputSystem.axisValue("exposure");
        if (exposure != 0.0)
        {
            camera->exposure += exposure * 5.0 * timeStep.value;
            camera->exposure = std::max(0.01, camera->exposure);
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
    if (scene().hasSystemType<DebugSystem>())
    {
        auto& debugSystem = scene().system<DebugSystem>();
        debugSystem.toggleShowInterface();
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
        default:
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
