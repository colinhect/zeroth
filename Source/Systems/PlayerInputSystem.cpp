///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

using namespace zeroth;

PlayerInputSystem::PlayerInputSystem(Scene& scene, CameraSystem& cameraSystem, InputSystem& inputSystem, Platform& platform) :
    System(scene),
    _cameraSystem(cameraSystem),
    _inputSystem(inputSystem),
    _platform(platform)
{
    platform.keyboard().registerListener(*this);
    platform.mouse().setMode(MouseMode::Relative);
}

void PlayerInputSystem::handlePlayerInput(Seconds timeStep)
{
    adjustCameraExposure(timeStep);
}

void PlayerInputSystem::adjustCameraExposure(Seconds timeStep)
{
    // Adjust the exposure of the active camera
    CameraComponent::Iterator camera = _cameraSystem.activeCamera();
    if (camera)
    {
        double exposure = _inputSystem.axisValue("exposure");
        if (exposure != 0.0)
        {
            camera->exposure += exposure * 5.0 * timeStep.value;
            camera->exposure = std::max(0.01, camera->exposure);
        }
    }
}

void PlayerInputSystem::swapMouseMode()
{
    Mouse& mouse = _platform.mouse();
    const MouseMode mode = mouse.mode();
    if (mode == MouseMode::Cursor)
    {
        mouse.setMode(MouseMode::Relative);
    }
    else
    {
        mouse.setMode(MouseMode::Cursor);
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
