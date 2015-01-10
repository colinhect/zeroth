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
    drawLoadingScreen(engine);

    // Load the scene
    AssetCache& assetCache = engine.assetCache();
    Path scenePath = engine.settings()["scene"].asString();
    _scene = assetCache.getHandle<Scene>(scenePath, engine);

    _font = assetCache.getHandle<Font>("Hect/Default.ttf");

    _mouse.setMode(MouseMode_Relative);
    _keyboard.addListener(*this);
}

void ZerothGameMode::tick(Engine& engine, Real timeStep)
{
    (void)engine;
    _scene->tick(timeStep);
}

void ZerothGameMode::render(Engine& engine, RenderTarget& target)
{
    SceneRenderer& sceneRenderer = engine.sceneRenderer();
    sceneRenderer.render(*_scene, target);

    InterfaceRenderer& interfaceRenderer = engine.interfaceRenderer();
    interfaceRenderer.beginFrame(target);
    interfaceRenderer.selectFont(*_font, 30);
    interfaceRenderer.drawText(Vector2(500, 500), "Testing... 1 2 3");
    interfaceRenderer.endFrame();
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

void ZerothGameMode::drawLoadingScreen(Engine& engine)
{
    AssetCache& assetCache = engine.assetCache();

    Font& font = assetCache.get<Font>("Hect/Default.ttf");

    InterfaceRenderer& interfaceRenderer = engine.interfaceRenderer();
    interfaceRenderer.beginFrame(engine.window());
    interfaceRenderer.selectFont(font, 30);
    interfaceRenderer.drawText(Vector2(100, 100), "Loading...");
    interfaceRenderer.endFrame();

    engine.window().swapBuffers();
}