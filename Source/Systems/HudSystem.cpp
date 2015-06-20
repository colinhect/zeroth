///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "HudSystem.h"

using namespace zeroth;

HudSystem::HudSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _assetCache(engine.assetCache()),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
    _widgetSystem(scene.system<WidgetSystem>())
{
}

void HudSystem::initialize()
{
    if (_widgetSystem)
    {
        Font::Handle font = _assetCache.getHandle<Font>("UI/Default.font");

        Label::Handle label(new Label("Testing...", Vector2(100, 100), Vector2(100, 100), font, 16));
        _widgetSystem->add(label);
    }
}

void HudSystem::tick(double timeStep)
{
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
}
