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

static const Path IntergalacticScenePath("Scenes/Intergalactic.scene");

}

ClientScene::ClientScene(Engine& engine) :
    Scene(engine),
    _interfaceSystem(*this, engine.platform(), engine.renderer(), engine.vectorRenderer()),
    _debugSystem(*this, _interfaceSystem),
    _inputSystem(*this, engine.platform(), engine.settings()),
    _cameraSystem(*this),
    _boundingBoxSystem(*this),
    _transformSystem(*this, _boundingBoxSystem),
    _playerInputSystem(*this, _inputSystem, _transformSystem, engine.platform()),
    _intergalacticScene(engine),
    _interstellarScene(engine),
    _stellarScene(engine),
    _sceneRenderer(engine.assetCache(), engine.taskPool())
{
    _intergalacticScene.load(IntergalacticScenePath);
}

void ClientScene::initialize()
{
    createInterface();
    _localPlayerEntity = entities().findFirstByName("LocalPlayer");

    _intergalacticScene.setObserver(*_localPlayerEntity);
    _intergalacticScene.initialize();

    Scene::initialize();
}

void ClientScene::tick(Seconds timeStep)
{
    _inputSystem.updateAxes(timeStep);

    if (_localPlayerEntity)
    {
        _playerInputSystem.handlePlayerInput(timeStep, *_localPlayerEntity);
    }

    _debugSystem.clearEnqueuedDebugGeometry();

    _intergalacticScene.tick(timeStep);
    _interstellarScene.tick(timeStep);
    _stellarScene.tick(timeStep);

    _interfaceSystem.tickAllInterfaces(timeStep);

    refresh();
}

void ClientScene::render(RenderTarget& target)
{
    Renderer& renderer = engine().renderer();
    _sceneRenderer.render(_intergalacticScene, _cameraSystem, renderer, target);
    //_sceneRenderer.render(*this, _cameraSystem, renderer, target);
    _interfaceSystem.renderAllInterfaces();
}

void ClientScene::createInterface()
{
    Window& mainWindow = engine().mainWindow();
    _interface = _interfaceSystem.createInterface(mainWindow);

    LabelWidget::Handle label = _interface->createChild<LabelWidget>();
    label->setText("Testing...");
}
