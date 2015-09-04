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
    if (_interfaceSystem)
    {
        Font::Handle font = _interfaceSystem->defaultFont;
        double fontSize = _interfaceSystem->defaultFontSize;

        _messageLog = _interfaceSystem->add<MessageLog>(Vector2(5, 0), Vector2(_window.width(), _window.height()), font, fontSize);
    }
}

void HudSystem::tick(double timeStep)
{
    std::lock_guard<std::mutex> lock(_pendingMessagesMutex);
    for (const std::string& message : _pendingMessages)
    {
        _messageLog->addMessage(message);
    }
    _pendingMessages.clear();
}

void HudSystem::receiveEvent(const KeyboardEvent& event)
{
}

void HudSystem::receiveEvent(const LogMessageEvent& event)
{
    std::lock_guard<std::mutex> lock(_pendingMessagesMutex);
    _pendingMessages.push_back(event.message);
}
