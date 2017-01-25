///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ClientScene.h"

using namespace zeroth;

ClientScene::ClientScene(Engine& engine) :
    Scene(engine),
    _cameraSystem(createSystem<CameraSystem>()),
    _debugSystem(createSystem<DebugSystem>()),
    _inputSystem(createSystem<InputSystem>()),
    _interfaceSystem(createSystem<InterfaceSystem>()),
    _renderSystem(createSystem<RenderSystem>()),
    _intergalacticScene(engine),
    _interstellarScene(engine),
    _stellarScene(engine)
{
}

void ClientScene::initialize()
{
    Scene::initialize();
    createInterface();
}

void ClientScene::tick(Seconds timeStep)
{
    _inputSystem.updateAxes(timeStep);
    _debugSystem.clearEnqueuedDebugGeometry();

    _intergalacticScene.tick(timeStep);
    _interstellarScene.tick(timeStep);
    _stellarScene.tick(timeStep);

    refresh();
}

void ClientScene::render(RenderTarget& target)
{
    _renderSystem.render(_intergalacticScene, target);
    _interfaceSystem.renderAllInterfaces();
}

void ClientScene::createInterface()
{
    Window& mainWindow = engine().mainWindow();
    _interface = _interfaceSystem.createInterface(mainWindow);

    LabelWidget::Handle label = _interface->createChild<LabelWidget>();
    label->setText("Testing...");
}
