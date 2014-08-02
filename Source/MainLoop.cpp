///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "MainLoop.h"

#include <Hect/IO/Data.h>

MainLoop::MainLoop(Engine& engine) :
    Loop(TimeSpan::fromSeconds((Real)1 / (Real)60)),
    _assetCache(&engine.assetCache()),
    _input(&engine.inputSystem()),
    _window(&engine.window()),
    _scene(engine.inputSystem(), engine.assetCache(), engine.renderer())
{
    AssetHandle<Data> sceneData = _assetCache->getHandle<Data>("Test/Scene.scene");
    _scene.decodeFromData(*sceneData, *_assetCache);

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);
}

MainLoop::~MainLoop()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(*this);
}

void MainLoop::fixedUpdate(Real timeStep)
{
    _input->updateAxes(timeStep);
    _scene.update(timeStep);
}

void MainLoop::frameUpdate(Real delta)
{
    _scene.render(delta, *_window);
    _window->swapBuffers();
}

void MainLoop::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType_KeyDown)
    {
        return;
    }

    if (event.key == Key_Esc)
    {
        setActive(false);
    }
}