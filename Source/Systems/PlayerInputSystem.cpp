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

PlayerInputSystem::PlayerInputSystem(Scene& scene, InputSystem& input_system, TransformSystem& transform_system, Platform& platform) :
    System(scene),
    _input_system(input_system),
    _transform_system(transform_system),
    _keyboard(platform.keyboard()),
    _mouse(platform.mouse())
{
    _keyboard.register_listener(*this);
    _mouse.set_mode(MouseMode::Relative);
}

void PlayerInputSystem::handle_player_input(Seconds time_step, Entity& local_player_entity)
{
    if (_mouse.mode() == MouseMode::Relative)
    {
        const double look_speed = 20.0 * time_step.value;
        const double roll_speed = 2.0 * time_step.value;
        const double move_speed = 100.0 * time_step.value;

        auto& transform = local_player_entity.component<TransformComponent>();
        auto& camera = local_player_entity.component<CameraComponent>();

        transform.local_rotation *= Quaternion::from_axis_angle(camera.up, Radians(_input_system.axis_value("Yaw") * -look_speed));
        transform.local_rotation *= Quaternion::from_axis_angle(camera.right, Radians(_input_system.axis_value("Pitch") * look_speed));
        transform.local_rotation *= Quaternion::from_axis_angle(camera.front, Radians(_input_system.axis_value("Roll") * -roll_speed));

        transform.local_position += camera.right * _input_system.axis_value("ThrustX") * move_speed;
        transform.local_position += camera.front * _input_system.axis_value("ThrustY") * move_speed;
        transform.local_position += camera.up * _input_system.axis_value("ThrustZ") * move_speed;

        _transform_system.commit_transform(transform);
    }
}

void PlayerInputSystem::swap_mouse_mode()
{
    const MouseMode mode = _mouse.mode();
    if (mode == MouseMode::Cursor)
    {
        _mouse.set_mode(MouseMode::Relative);
    }
    else
    {
        _mouse.set_mode(MouseMode::Cursor);
    }
}

void PlayerInputSystem::parse_keyboard_shortcut(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType::KeyDown)
    {
        switch (event.key)
        {
        case Key::Tab:
            swap_mouse_mode();
            break;
        case Key::Esc:
            deactivate_scene();
            break;
        default:
            break;
        }
    }
}

void PlayerInputSystem::deactivate_scene()
{
    scene().set_active(false);
}

void PlayerInputSystem::receive_event(const KeyboardEvent& event)
{
    parse_keyboard_shortcut(event);
}
