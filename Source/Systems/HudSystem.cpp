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
#include "HudSystem.h"
#include "Components/StarComponent.h"
#include "Scenes/StellarScene.h"

using namespace zeroth;

HudSystem::HudSystem(Scene& scene, StellarScene& stellar_scene, InterfaceSystem& interface_system, Window& window) :
    System(scene),
    _stellar_scene(stellar_scene),
    _window(window),
    _interface_system(interface_system)
{
    register_log_listener(*this);

    _interface = _interface_system.create_interface(_window);
    _camera_position_label = _interface->create_child<LabelWidget>();
}

void HudSystem::update_widgets()
{
    auto star = _stellar_scene.components<StarComponent>().begin();
    if (star)
    {
        _camera_position_label->set_text(format("Absolute Magnitude: %f", star->absolute_magnitude));
    }
}

void HudSystem::receive_event(const KeyboardEvent& event)
{
    (void)event;
}

void HudSystem::receive_event(const LogMessageEvent& event)
{
    (void)event;
}
