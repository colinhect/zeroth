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
    _mouse(engine.platform().mouse()),
    _cameraSystem(scene.system<CameraSystem>()),
    _inputSystem(scene.system<InputSystem>()),
    _debugSystem(scene.system<DebugSystem>())
{
    Keyboard& keyboard = engine.platform().keyboard();
    keyboard.registerListener(*this);

    _mouse.setMode(MouseMode_Relative);
}

void GameplaySystem::tick(double timeStep)
{
    if (_cameraSystem)
    {
        Camera::Iterator camera = _cameraSystem->activeCamera();
        if (camera)
        {
            if (_inputSystem)
            {
                double exposure = _inputSystem->axisValue("exposure");
                camera->exposure += exposure * 5.0 * timeStep;
            }
        }
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
            if (_debugSystem)
            {
                bool enabled = _debugSystem->isEnabled();
                _debugSystem->setEnabled(!enabled);
            }
        }
        else if (event.key == Key_Esc)
        {
            scene().setActivate(false);
        }
    }
}