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
#include "ClientScene.h"

using namespace zeroth;

namespace
{
    const Path IntergalacticScenePath("Scenes/Intergalactic.scene");
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

    // Integrate content/asset generation from source files (from blender, YAML files, etc) to deserializable binary formats into the CMake build system.  Data is code, code is data... don't feel bad about hardcoding references to asset paths.  Write in Python, make extensible for adding any toolchain to the asset build process.  Could be a niche open source engine/framework for those who like manual control of a simple unified build system.

    Scene::initialize();
}

void ClientScene::tick(Seconds timeStep)
{
    _inputSystem.updateAxes(timeStep);

    if (_localPlayerEntity)
    {
        _playerInputSystem.handlePlayerInput(timeStep, *_localPlayerEntity);
    }

    _intergalacticScene.tick(timeStep);
    _interstellarScene.tick(timeStep);
    _stellarScene.tick(timeStep);

    _transformSystem.updateCommittedTransforms();
    _cameraSystem.updateAllCameras();

    _interfaceSystem.tickAllInterfaces(timeStep);

    refresh();
}

void ClientScene::render(RenderTarget& target)
{
    Renderer& renderer = engine().renderer();

    //_sceneRenderer.render(_intergalacticScene, _cameraSystem, renderer, target);
    _sceneRenderer.render(*this, _cameraSystem, renderer, target);

    _interfaceSystem.renderAllInterfaces();
}

void ClientScene::createInterface()
{
    Window& mainWindow = engine().mainWindow();
    _interface = _interfaceSystem.createInterface(mainWindow);

    LabelWidget::Handle label = _interface->createChild<LabelWidget>();
    label->setText("Testing... One two three and stuff");
}
