///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ClientScene.h"

using namespace zeroth;

namespace
{

static const Path LocalPlayerBaseEntityPath("Entities/LocalPlayerBase.entity");

}

ClientScene::ClientScene(Engine& engine) :
    Scene(engine),
    _interfaceSystem(engine, *this),
    _debugSystem(engine, *this, _interfaceSystem),
    _inputSystem(engine, *this),
    _cameraSystem(engine, *this),
    _renderSystem(engine, *this, _cameraSystem, _debugSystem),
    _playerInputSystem(engine, *this, _cameraSystem, _inputSystem),
    _intergalacticScene(engine),
    _interstellarScene(engine),
    _stellarScene(engine)
{
}

void ClientScene::initialize()
{
    Scene::initialize();

    createInterface();
    createLocalPlayerEntity();
}

void ClientScene::tick(Seconds timeStep)
{
    _inputSystem.updateAxes(timeStep);
    _playerInputSystem.handlePlayerInput(timeStep);

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

void ClientScene::createLocalPlayerEntity()
{
    if (_localPlayerEntity)
    {
        throw InvalidOperation("Local player entity already exists");
    }

    _localPlayerEntity = loadEntity(LocalPlayerBaseEntityPath)->createHandle();
    _localPlayerEntity->activate();
}
