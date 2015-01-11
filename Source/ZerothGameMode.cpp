///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard())
{
    AssetCache& assetCache = engine.assetCache();
    const DataValue& settings = engine.settings();

    // Render the loading screen
    renderLoadingScreen(engine);

    // Load assets
    Path scenePath = settings["scene"].asString();
    _scene = assetCache.getHandle<Scene>(scenePath, engine);
    _font = assetCache.getHandle<Font>("Hect/Default.ttf");

    // Pre-upload all render objects in the scene
    SceneRenderer& sceneRenderer = engine.sceneRenderer();
    sceneRenderer.uploadRendererObjects(*_scene);

    // Wait until all assets are loaded
    assetCache.taskPool().wait();

    _mouse.setMode(MouseMode_Relative);
    _keyboard.addListener(*this);
}

bool ZerothGameMode::tick(Engine& engine, Real timeStep)
{
    (void)engine;

    _scene->tick(timeStep);
    return _active;
}

void ZerothGameMode::render(Engine& engine, RenderTarget& target)
{
    SceneRenderer& sceneRenderer = engine.sceneRenderer();
    sceneRenderer.render(*_scene, target);
}

void ZerothGameMode::receiveEvent(const KeyboardEvent& event)
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

void ZerothGameMode::renderLoadingScreen(Engine& engine)
{
    AssetCache& assetCache = engine.assetCache();

    Font& font = assetCache.get<Font>("Hect/Default.ttf");

    Window& window = engine.window();

    VectorRenderer& vectorRenderer = engine.vectorRenderer();
    vectorRenderer.beginFrame(window);
    vectorRenderer.setFillColor(Color(0.7, 0.7, 0.7));
    vectorRenderer.setFont(font, 15);
    vectorRenderer.text("Loading...", Rectangle(0, 0, window.width(), window.height()));
    vectorRenderer.endFrame();

    window.swapBuffers();
}