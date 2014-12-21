///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include "Components/CockpitCamera.h"

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds(Real(1) / Real(60))),
    _sceneRenderer(engine.renderer(), engine.assetCache())
{
    AssetCache& assetCache = engine.assetCache();
    _scene = assetCache.getHandle<Scene>("Test/Test.scene", engine);

    _observerEntity = _scene->createEntity();
    {
        AssetDecoder decoder(engine.assetCache(), "Test/Observer.entity");
        decoder >> decodeValue(*_observerEntity);
    }
    
    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.addListener(*this);
}

void ZerothGameMode::tick()
{
    _scene->tick(timeStep());
}

void ZerothGameMode::render(RenderTarget& target)
{
    _sceneRenderer.renderScene(*_scene, target);
}

void ZerothGameMode::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown && event.key == Key_F1)
    {
        if (_scene->hasSystemType<DebugSystem>())
        {
            _scene->removeSystemType<DebugSystem>();
        }
        else
        {
            _scene->addSystemType<DebugSystem>();
        }
    }
    
    if (event.type == KeyboardEventType_KeyDown && event.key == Key_Q)
    {
        if (_activeObserver)
        {
            Entity::Iterator cockpitEntity = _scene->entities().findFirst([] (const Entity& entity)
            {
                return entity.component<CockpitCamera>();
            });

            _scene->system<CameraSystem>().setActiveCamera(*cockpitEntity->component<Camera>());

            _activeObserver = Entity::Handle();
        }
        else
        {
            _activeObserver = _observerEntity->clone()->createHandle();
            _activeObserver->activate();
            _scene->system<CameraSystem>().setActiveCamera(*_activeObserver->component<Camera>());
        }
    }
}