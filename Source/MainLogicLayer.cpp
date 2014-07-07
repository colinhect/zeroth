///////////////////////////////////////////////////////////////////////////////
// This source file is part of Hect.
//
// Copyright (c) 2014 Colin Hill
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
#include "MainLogicLayer.h"

#include <Hect/Logic/Components/Geometry.h>
#include <Hect/Logic/Components/Transform.h>
#include <Hect/Logic/Components/RigidBody.h>
#include <Hect/Debug/TransformDebugRenderLayer.h>

MainLogicLayer::MainLogicLayer(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _taskPool(1),
    _renderSystem(_scene, renderer),
    _transformSystem(_scene),
    _physicsSystem(_scene, _taskPool),
    _debugSystem(_scene),
    _playerCameraSystem(_scene, inputSystem)
{
    _scene.registerComponent<PlayerCamera>("PlayerCamera");

    _debugSystem.addRenderLayer(Key::F5, new TransformDebugRenderLayer(assetCache));

    {
        JsonValue& jsonValue = assetCache.get<JsonValue>("Player.entity");

        _player = _scene.createEntity();
        _player->decodeFromJsonValue(jsonValue, assetCache);
        _player->activate();
    }

    {
        JsonValue& jsonValue = assetCache.get<JsonValue>("Cube.entity");

        _cube = _scene.createEntity();
        _cube->decodeFromJsonValue(jsonValue, assetCache);

        _cube->clone()->activate();
    }

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);
    keyboardDispatcher.addListener(_debugSystem);

    Mouse& mouse = _input->mouse();
    mouse.setMode(MouseMode::Relative);
}

MainLogicLayer::~MainLogicLayer()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(_debugSystem);
    keyboardDispatcher.removeListener(*this);
}

void MainLogicLayer::fixedUpdate(Real timeStep)
{
    _input->updateAxes(timeStep);

    _physicsSystem.endAsynchronousUpdate();

    _playerCameraSystem.update(timeStep);
    _renderSystem.updateActiveCamera();
    _transformSystem.update();

    _physicsSystem.beginAsynchronousUpdate(timeStep, 4);
}

void MainLogicLayer::frameUpdate(Real delta)
{
    delta;

    _renderSystem.renderAll(*_window);
    _debugSystem.renderActivatedRenderLayers(_renderSystem, *_window);

    _window->swapBuffers();
}

void MainLogicLayer::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setActive(false);
    }

    if (event.key == Key::Tab)
    {
        Mouse& mouse = _input->mouse();
        if (mouse.mode() == MouseMode::Cursor)
        {
            mouse.setMode(MouseMode::Relative);
        }
        else
        {
            mouse.setMode(MouseMode::Cursor);
        }
    }

    if (event.key == Key::F)
    {
        Entity::Iter cloneEntity = _cube->clone();

        auto transform = cloneEntity->component<Transform>();
        if (transform)
        {
            transform->setPosition(_player->component<Transform>()->position());
        }

        auto rigidBody = cloneEntity->component<RigidBody>();
        if (rigidBody)
        {
            rigidBody->setLinearVelocity(_player->component<Camera>()->front() * 15.0f);
        }

        cloneEntity->activate();
    }
}