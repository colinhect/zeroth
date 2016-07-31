///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT HudSystem :
    public System<HudSystem>,
    public Listener<KeyboardEvent>,
    public Listener<LogMessageEvent>
{
public:
    HudSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep);
    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const LogMessageEvent& event) override;

private:
    AssetCache& _assetCache;
    Window& _window;
    Keyboard& _keyboard;
    Mouse& _mouse;

    InterfaceSystem::Handle _interfaceSystem;
    Interface::Handle _interface;
    Label::Handle _cameraPositionLabel;
};

}
