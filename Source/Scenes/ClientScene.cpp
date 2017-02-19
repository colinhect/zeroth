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
    _interfaceSystem(engine, *this),
    _debugSystem(engine, *this, _interfaceSystem),
    _inputSystem(engine, *this),
    _cameraSystem(engine, *this),
    _renderSystem(engine, *this, _cameraSystem, _debugSystem),
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

    _interfaceSystem.tickAllInterfaces(timeStep);

    refresh();
}

void ClientScene::render(RenderTarget& target)
{
    _renderSystem.render(_intergalacticScene, target);
    _renderSystem.render(*this, target);
    _interfaceSystem.renderAllInterfaces();
}

void ClientScene::createInterface()
{
    Window& mainWindow = engine().mainWindow();
    _interface = _interfaceSystem.createInterface(mainWindow);

    LabelWidget::Handle label = _interface->createChild<LabelWidget>();
    label->setText("Testing...");
}
