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
    _scene(engine)
{
    {
        JsonValue& jsonValue = _assetCache->get<JsonValue>("Test/Scene.scene");
        _scene.decodeFromJsonValue(jsonValue, *_assetCache);
    }

    _player = _scene.createEntity("Test/Player.entity", engine.assetCache());
    _player->activate();

    _test = _scene.createEntity("Test/MaterialTest.entity", engine.assetCache());

    for (float x = 0; x < 5; ++x)
    {
        for (float z = 0; z < 5; ++z)
        {
            Entity::Iter entity = _scene.createEntity("Test/MaterialTest.entity", engine.assetCache());
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
   
}

ServerLoop::~ServerLoop()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(*this);
}

void ServerLoop::fixedUpdate(Real timeStep)
{
    _input->updateAxes(timeStep);
    _scene.update(timeStep);
}

void ServerLoop::frameUpdate(Real delta)
{
    _scene.render(delta, *_window);
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