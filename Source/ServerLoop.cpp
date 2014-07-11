///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ServerLoop.h"

#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Graphics/Components/Geometry.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

ServerLoop::ServerLoop(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
    Loop(TimeSpan::fromSeconds((Real)1 / (Real)60)),
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _taskPool(4),
    _renderSystem(_scene, renderer),
    _transformSystem(_scene),
    _boundingBoxSystem(_scene),
    _physicsSystem(_scene, _taskPool),
    _debugSystem(_scene),
    _playerCameraSystem(_scene, inputSystem),
    _transformDebugRenderLayer(assetCache),
    _boundingBoxDebugRenderLayer(assetCache)
{
    _debugSystem.addRenderLayer(Key_F5, _transformDebugRenderLayer);
    _debugSystem.addRenderLayer(Key_F6, _boundingBoxDebugRenderLayer);

    {
        JsonValue& jsonValue = assetCache.get<JsonValue>("Test/Player.entity");

        _player = _scene.createEntity();
        _player->decodeFromJsonValue(jsonValue, assetCache);
        _player->activate();
    }

    {
        JsonValue& jsonValue = assetCache.get<JsonValue>("Test/Cube.entity");

        _cube = _scene.createEntity();
        _cube->decodeFromJsonValue(jsonValue, assetCache);

        _cube->clone()->activate();
    }

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);
    keyboardDispatcher.addListener(_debugSystem);

    Mouse& mouse = _input->mouse();
    mouse.setMode(MouseMode_Relative);
}

ServerLoop::~ServerLoop()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(_debugSystem);
    keyboardDispatcher.removeListener(*this);
}

void ServerLoop::fixedUpdate(Real timeStep)
{
    _input->updateAxes(timeStep);

    _physicsSystem.endAsynchronousUpdate();

    _playerCameraSystem.update(timeStep);
    _renderSystem.updateActiveCamera();
    _transformSystem.update();
    _boundingBoxSystem.update();

    _physicsSystem.beginAsynchronousUpdate(timeStep, 4);
}

void ServerLoop::frameUpdate(Real delta)
{
    delta;

    _renderSystem.renderAll(*_window);
    _debugSystem.renderActivatedRenderLayers(_renderSystem, *_window);

    _window->swapBuffers();
}

void ServerLoop::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType_KeyDown)
    {
        return;
    }

    if (event.key == Key_Esc)
    {
        setActive(false);
    }

    if (event.key == Key_Tab)
    {
        Mouse& mouse = _input->mouse();
        if (mouse.mode() == MouseMode_Cursor)
        {
            mouse.setMode(MouseMode_Relative);
        }
        else
        {
            mouse.setMode(MouseMode_Cursor);
        }
    }

    if (event.key == Key_F)
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