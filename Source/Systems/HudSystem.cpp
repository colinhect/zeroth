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
    _mouse(engine.mouse())
{
    registerLogListener(*this);
}

void HudSystem::updateWidgets()
{
    auto& cameraSystem = scene().system<CameraSystem>();
    CameraComponent::Iterator camera = cameraSystem.activeCamera();
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
    auto& interfaceSystem = scene().system<InterfaceSystem>();
    _interface = interfaceSystem.createInterface(_window);
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
