///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ServerLoop.h"

#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

#include "RegisterComponents.h"

ServerLoop::ServerLoop(Engine& engine) :
    Loop(TimeSpan::fromSeconds((Real)1 / (Real)60)),
    _assetCache(&engine.assetCache()),
    _input(&engine.inputSystem()),
    _window(&engine.window()),
    _taskPool(4),
    _scene(engine.assetCache(), registerComponents),
    _renderSystem(_scene, engine.renderer(), engine.assetCache()),
    _debugRenderSystem(_scene, engine.renderer()),
    _transformSystem(_scene),
    _boundingBoxSystem(_scene),
    _physicsSystem(_scene, _taskPool),
    _playerCameraSystem(_scene, engine.inputSystem()),
    _transformDebugRenderLayer(engine.assetCache()),
    _boundingBoxDebugRenderLayer(engine.assetCache())
{
    _debugRenderSystem.addRenderLayer(Key_F5, _transformDebugRenderLayer);
    _debugRenderSystem.addRenderLayer(Key_F6, _boundingBoxDebugRenderLayer);

    {
        JsonValue& jsonValue = _assetCache->get<JsonValue>("Test/Scene.scene");
        _scene.decodeFromJsonValue(jsonValue, *_assetCache);
    }

    _player = _scene.createEntity("Test/Player.entity");
    _player->activate();

    _test = _scene.createEntity("Test/MaterialTest.entity");

    for (float x = 0; x < 5; ++x)
    {
        for (float z = 0; z < 5; ++z)
        {
            Entity::Iter entity = _scene.createEntity("Test/MaterialTest.entity");
            entity->component<Transform>()->translate(Vector3(x, 0, z) * 6);

            auto model = entity->component<Model>();
            
            Pass pass;
            pass.setShader(_assetCache->getHandle<Shader>("Hect/PhysicallyBased/Solid.shader"));
            pass.addUniformValue("diffuse", Vector3(0.5, 0.5, 0.5));
            pass.addUniformValue("roughness", x / 4);
            pass.addUniformValue("metallic", z / 4);
           
            Technique technique;
            technique.addPass(pass);

            AssetHandle<Material> material(new Material());
            material->addTechnique(technique);      
            
            model->surfaces().begin()->material() = material;

            entity->activate();
        }
    }

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);
    keyboardDispatcher.addListener(_debugRenderSystem);

    Mouse& mouse = _input->mouse();
    mouse.setMode(MouseMode_Relative);
}

ServerLoop::~ServerLoop()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(_debugRenderSystem);
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
    _debugRenderSystem.renderAll(*_window);

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
        Entity::Iter cloneEntity = _test->clone();

        cloneEntity->replaceComponent(*_player->component<Transform>());

        auto rigidBody = cloneEntity->component<RigidBody>();
        if (rigidBody)
        {
            rigidBody->setLinearVelocity(_player->component<Camera>()->front() * 15.0f);
        }

        cloneEntity->activate();
    }
}