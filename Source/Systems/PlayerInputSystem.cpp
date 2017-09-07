///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2017 Colin Hill
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////
#include "PlayerInputSystem.h"

using namespace zeroth;

PlayerInputSystem::PlayerInputSystem(Scene& scene, InputSystem& inputSystem, TransformSystem& transformSystem, Platform& platform) :
    System(scene),
    _inputSystem(inputSystem),
    _transformSystem(transformSystem),
    _keyboard(platform.keyboard()),
    _mouse(platform.mouse())
{
    _keyboard.registerListener(*this);
    _mouse.setMode(MouseMode::Relative);
}

void PlayerInputSystem::handlePlayerInput(Seconds timeStep, Entity& localPlayerEntity)
{
    if (_mouse.mode() == MouseMode::Relative)
    {
        const double lookSpeed = 20.0 * timeStep.value;
        const double rollSpeed = 2.0 * timeStep.value;
        const double moveSpeed = 100.0 * timeStep.value;

        auto& transform = localPlayerEntity.component<TransformComponent>();
        auto& camera = localPlayerEntity.component<CameraComponent>();

        transform.localRotation *= Quaternion::fromAxisAngle(camera.up, Radians(_inputSystem.axisValue("yaw") * -lookSpeed));
        transform.localRotation *= Quaternion::fromAxisAngle(camera.right, Radians(_inputSystem.axisValue("pitch") * lookSpeed));
        transform.localRotation *= Quaternion::fromAxisAngle(camera.front, Radians(_inputSystem.axisValue("roll") * -rollSpeed));

        transform.localPosition += camera.right * _inputSystem.axisValue("thrustX") * moveSpeed;
        transform.localPosition += camera.front * _inputSystem.axisValue("thrustY") * moveSpeed;
        transform.localPosition += camera.up * _inputSystem.axisValue("thrustZ") * moveSpeed;

        _transformSystem.commitTransform(transform);
    }
}

void PlayerInputSystem::swapMouseMode()
{
    const MouseMode mode = _mouse.mode();
    if (mode == MouseMode::Cursor)
    {
        _mouse.setMode(MouseMode::Relative);
    }
    else
    {
        _mouse.setMode(MouseMode::Cursor);
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
