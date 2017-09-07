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

using namespace zeroth;

HudSystem::HudSystem(Scene& scene, CameraSystem& cameraSystem, InterfaceSystem& interfaceSystem) :
    System(scene),
    //_assetCache(engine.assetCache()),
    //_window(engine.mainWindow()),
    //_keyboard(engine.keyboard()),
    //_mouse(engine.mouse()),
    _cameraSystem(cameraSystem),
    _interfaceSystem(interfaceSystem)
{
    registerLogListener(*this);
}

void HudSystem::updateWidgets()
{
    CameraComponent::Iterator camera = _cameraSystem.activeCamera();
    if (camera)
    {
        auto& transform = camera->entity().component<TransformComponent>();
        Vector3 position = transform.localPosition;
        _cameraPositionLabel->setText(format("%f %f %f", position.x, position.y, position.z));
    }
}

void HudSystem::initialize()
{
    //_interface = _interfaceSystem.createInterface(_window);
    //_cameraPositionLabel = _interface->createChild<LabelWidget>();
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
    (void)event;
}

void HudSystem::receiveEvent(const LogMessageEvent& event)
{
    (void)event;
}
