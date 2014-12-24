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

    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.addListener(*this);
}

void ZerothGameMode::tick(Real timeStep)
{
    _scene->tick(timeStep);
}

void ZerothGameMode::render(RenderTarget& target)
{
    _sceneRenderer.renderScene(*_scene, target);
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
        Mouse& mouse = engine().platform().mouse();
        if (mouse.mode() == MouseMode_Cursor)
        {
            mouse.setMode(MouseMode_Relative);
        }
        else
        {
            mouse.setMode(MouseMode_Cursor);
        }
    }
}