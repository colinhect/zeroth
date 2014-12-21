///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

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
            // Restore the last active camera
            if (_lastActiveCamera)
            {
                auto camera = _lastActiveCamera->component<Camera>();
                if (camera)
                {
                    _scene->system<CameraSystem>().setActiveCamera(*camera);
                }

                _lastActiveCamera = Entity::Handle();
            }

            // Issue #149
            _activeObserver = Entity::Handle();
        }
        else
        {
            // Remember the active camera
            auto camera = _scene->system<CameraSystem>().activeCamera();
            if (camera)
            {
                _lastActiveCamera = camera->entity().createHandle();
            }

            // Instantiate an observer
            auto observer = _observerEntity->clone();
            observer->activate();

            // Set as active observer
            _activeObserver = observer->createHandle();

            // Set active camera
            auto observerCamera = _activeObserver->component<Camera>();
            if (observerCamera)
            {
                _scene->system<CameraSystem>().setActiveCamera(*observerCamera);
            }
        }
    }
}