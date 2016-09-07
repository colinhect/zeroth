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
    public EventListener<KeyboardEvent>,
    public EventListener<LogMessageEvent>
{
public:
    HudSystem(Engine& engine, Scene& scene);

    void updateWidgets();

private:
    // System overrides
    void initialize() override;

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const LogMessageEvent& event) override;

    AssetCache& _assetCache;
    Window& _window;
    Keyboard& _keyboard;
    Mouse& _mouse;

    InterfaceSystem::Handle _interfaceSystem;
    Interface::Handle _interface;
    LabelWidget::Handle _cameraPositionLabel;
};

}
