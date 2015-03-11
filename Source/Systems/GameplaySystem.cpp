///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GameplaySystem.h"

using namespace zeroth;

GameplaySystem::GameplaySystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _mouse(engine.platform().mouse())
{
    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.registerListener(*this);

    _mouse.setMode(MouseMode_Relative);
}

void GameplaySystem::tick(double timeStep)
{
    auto cameraSystem = scene().system<CameraSystem>();
    assert(cameraSystem);

    auto camera = cameraSystem->activeCamera();
    if (camera)
    {
        auto inputSystem = scene().system<InputSystem>();
        assert(inputSystem);

        double exposure = inputSystem->axisValue("exposure");
        camera->exposure += exposure * 5.0 * timeStep;
    }
}

void GameplaySystem::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown)
    {
        if (event.key == Key_Tab)
        {
            MouseMode mode = _mouse.mode();
            if (mode == MouseMode_Cursor)
            {
                _mouse.setMode(MouseMode_Relative);
            }
            else
            {
                _mouse.setMode(MouseMode_Cursor);
            }
        }
        else if (event.key == Key_F1)
        {
            auto debugSystem = scene().system<DebugSystem>();
            if (debugSystem)
            {
                bool enabled = debugSystem->isEnabled();
                debugSystem->setEnabled(!enabled);
            }
        }
        else if (event.key == Key_Esc)
        {
            scene().setActivate(false);
        }
    }
}