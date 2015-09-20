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
    _window(engine.window()),
    _keyboard(engine.keyboard()),
    _mouse(engine.mouse()),
    _interfaceSystem(scene.system<InterfaceSystem>())
{
    registerLogListener(*this);
}

void HudSystem::initialize()
{
}

void HudSystem::tick(double timeStep)
{
    (void)timeStep;
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
    (void)event;
}

void HudSystem::receiveEvent(const LogMessageEvent& event)
{
    (void)event;
}
