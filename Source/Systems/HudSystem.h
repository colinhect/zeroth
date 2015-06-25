///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include <mutex>
#include <vector>

namespace zeroth
{

/// \system
class HudSystem :
    public System<HudSystem>,
    public Listener<KeyboardEvent>,
    public Listener<LogMessageEvent>
{
public:
    HudSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const LogMessageEvent& event) override;

private:
    AssetCache& _assetCache;
    Window& _window;
    Keyboard& _keyboard;
    Mouse& _mouse;

    WidgetSystem::Handle _widgetSystem;
    MessageLog::Handle _messageLog;

    std::vector<std::string> _pendingMessages;
    std::mutex _pendingMessagesMutex;
};

}