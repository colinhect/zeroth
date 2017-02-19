///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "HudSystem.h"

using namespace zeroth;

HudSystem::HudSystem(Engine& engine, Scene& scene, CameraSystem& cameraSystem, InterfaceSystem& interfaceSystem) :
    System(engine, scene),
    _assetCache(engine.assetCache()),
    _window(engine.mainWindow()),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
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
        auto transform = camera->entity()->component<TransformComponent>();
        if (transform)
        {
            Vector3 position = transform->localPosition;
            _cameraPositionLabel->setText(format("%f %f %f", position.x, position.y, position.z));
        }
    }
}

void HudSystem::initialize()
{
    _interface = _interfaceSystem.createInterface(_window);
    _cameraPositionLabel = _interface->createChild<LabelWidget>();
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
    (void)event;
}

void HudSystem::receiveEvent(const LogMessageEvent& event)
{
    (void)event;
}
