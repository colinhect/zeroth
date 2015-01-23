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
    keyboard.addListener(*this);
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
            if (scene().hasSystemType<DebugSystem>())
            {
                scene().removeSystemType<DebugSystem>();
            }
            else
            {
                scene().addSystemType<DebugSystem>();
            }
        }
    }
}