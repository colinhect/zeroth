///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(TimeSpan::fromSeconds(Real(1) / Real(60))),
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard())
{
    // Draw the loading screen
    drawLoadingScreen(engine);

    // Load assets
    AssetCache& assetCache = engine.assetCache();
    Path scenePath = engine.settings()["scene"].asString();
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

    if (_scene->hasSystemType<DebugSystem>())
    {
        VectorRenderer& vectorRenderer = engine.vectorRenderer();
        vectorRenderer.beginFrame(target);

        Rectangle bounds(5, 5, 60, 25);

        vectorRenderer.beginPath();
        vectorRenderer.selectFillColor(Vector4(0, 0, 0, 0.5));
        vectorRenderer.rectangle(bounds);
        vectorRenderer.fill();

        vectorRenderer.selectFont(*_font, 18);
        vectorRenderer.selectFillColor(Vector4(1, 1, 1, 1));
        vectorRenderer.text("Debug", bounds, HorizontalAlign_Center, VerticalAlign_Center);

        vectorRenderer.endFrame();
    }
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

void ZerothGameMode::drawLoadingScreen(Engine& engine)
{
    AssetCache& assetCache = engine.assetCache();

    Font& font = assetCache.get<Font>("Hect/Default.ttf");

    Window& window = engine.window();

    VectorRenderer& vectorRenderer = engine.vectorRenderer();
    vectorRenderer.beginFrame(window);
    vectorRenderer.selectFont(font, 25);
    vectorRenderer.text("Loading...", Rectangle(0, 0, window.width(), window.height()));
    vectorRenderer.endFrame();

    window.swapBuffers();
}