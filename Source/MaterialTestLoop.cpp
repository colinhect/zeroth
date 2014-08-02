///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "MaterialTestLoop.h"

#include <Hect/Debug/TransformDebugRenderLayer.h>
#include <Hect/Debug/BoundingBoxDebugRenderLayer.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/IO/Data.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

MaterialTestLoop::MaterialTestLoop(Engine& engine) :
    Loop(TimeSpan::fromSeconds((Real)1 / (Real)60)),
    _assetCache(&engine.assetCache()),
    _input(&engine.inputSystem()),
    _window(&engine.window()),
    _taskPool(4),
    _scene(engine.inputSystem(), engine.assetCache(), engine.renderer())
{
    AssetHandle<Data> mineralTestEntityData = _assetCache->getHandle<Data>("Test/MaterialTest.entity");
    _test = _scene.createEntity()->createHandle();
    _test->decodeFromData(*mineralTestEntityData, engine.assetCache());

    AssetHandle<Data> sceneData = _assetCache->getHandle<Data>("Test/Scene.scene");
    _scene.decodeFromData(*sceneData, *_assetCache);

    for (float x = 0; x < 5; ++x)
    {
        for (float z = 0; z < 5; ++z)
        {
            Data& entityData = _assetCache->get<Data>("Test/Scene.scene");

            Entity::Iterator entity = _test->clone();
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

    _player = _scene.entities().findFirst([](const Entity& entity) { return entity.component<PlayerCamera>(); })->createHandle();

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);
}

MaterialTestLoop::~MaterialTestLoop()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(*this);
}

void MaterialTestLoop::fixedUpdate(Real timeStep)
{
    _input->updateAxes(timeStep);
    _scene.update(timeStep);
}

void MaterialTestLoop::frameUpdate(Real delta)
{
    _scene.render(delta, *_window);
    _window->swapBuffers();
}

void MaterialTestLoop::receiveEvent(const KeyboardEvent& event)
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
        Entity::Iterator cloneEntity = _test->clone();

        cloneEntity->replaceComponent<Transform>(*_player->component<Transform>());

        auto rigidBody = cloneEntity->component<RigidBody>();
        if (rigidBody)
        {
            rigidBody->setLinearVelocity(_player->component<Camera>()->front() * 15.0f);
        }

        cloneEntity->activate();
    }
}