///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "TestMode.h"

using namespace zeroth;

TestMode::TestMode(Engine& engine) :
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard())
{
    AssetCache& assetCache = engine.assetCache();
    const DataValue& settings = engine.settings();

    // Load assets
    Path scenePath = settings["scene"].asString();
    _scene = assetCache.getHandle<Scene>(scenePath, engine);

    // Pre-upload all render objects in the scene
    RenderSystem& renderSystem = _scene->system<RenderSystem>();
    renderSystem.uploadRendererObjects();

    // Wait until all assets are loaded
    assetCache.taskPool().wait();

    _mouse.setMode(MouseMode_Relative);
    _keyboard.addListener(*this);
}

bool TestMode::tick(Engine& engine, Real timeStep)
{
    _scene->tick(engine, timeStep);
    return _active;
}

void TestMode::render(Engine& engine, RenderTarget& target)
{
    _scene->render(engine, target);
}

void TestMode::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown)
    {
        if (event.key == Key_F1)
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
        else if (event.key == Key_Tab)
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
        else if (event.key == Key_Esc)
        {
            _active = false;
        }
    }
}
