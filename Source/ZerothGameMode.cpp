///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(TimeSpan::fromSeconds(Real(1) / Real(60))),
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard()),
    _sceneRenderer(engine.assetCache())
{
    // Load the scene
    AssetCache& assetCache = engine.assetCache();
    Path scenePath = engine.settings()["scene"].asString();
    _scene = assetCache.getHandle<Scene>(scenePath, engine);

    _keyboard.addListener(*this);
}

void ZerothGameMode::tick(Real timeStep)
{
    _scene->tick(timeStep);
}

void ZerothGameMode::render(Renderer& renderer, RenderTarget& target)
{
    _sceneRenderer.renderScene(renderer, *_scene, target);
}

void ZerothGameMode::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown && event.key == Key_F1)
    {
        // Toggle debug system
        if (_scene->hasSystemType<DebugSystem>())
        {
            _scene->removeSystemType<DebugSystem>();
        }
        else
        {
            _scene->addSystemType<DebugSystem>();
        }
    }
    else if (event.type == KeyboardEventType_KeyDown && event.key == Key_Tab)
    {
        // Toggle mouse cursor mode
        if (_mouse.mode() == MouseMode_Cursor)
        {
            _mouse.setMode(MouseMode_Relative);
        }
        else
        {
            _mouse.setMode(MouseMode_Cursor);
        }
    }
}