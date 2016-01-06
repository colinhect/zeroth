///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "HudSystem.h"

using namespace zeroth;

HudSystem::HudSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _assetCache(engine.assetCache()),
    _window(engine.window()),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
    _interfaceSystem(scene.system<InterfaceSystem>())
{
    registerLogListener(*this);
}

void HudSystem::initialize()
{
    if (_interfaceSystem)
    {
        _cameraPositionLabel = _interfaceSystem->addWidget<Label>();
    }
}

void HudSystem::tick(double timeStep)
{
    (void)timeStep;

    CameraSystem::Handle cameraSystem = scene().system<CameraSystem>();
    if (cameraSystem)
    {
        Camera::Iterator camera = cameraSystem->activeCamera();
        if (camera)
        {
            Transform::Iterator transform = camera->entity()->component<Transform>();
            if (transform)
            {
                const Vector3& position = transform->localPosition;
                _cameraPositionLabel->setText(format("%f %f %f", position.x, position.y, position.z));
            }
        }
    }
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
    (void)event;
}

void HudSystem::receiveEvent(const LogMessageEvent& event)
{
    (void)event;
}
