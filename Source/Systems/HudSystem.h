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
    HudSystem(Scene& scene, CameraSystem& cameraSystem, InterfaceSystem& interfaceSystem);

    void updateWidgets();

private:
    void initialize();

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const LogMessageEvent& event) override;

    //AssetCache& _assetCache;
    //Window& _window;
    //Keyboard& _keyboard;
    //Mouse& _mouse;

    CameraSystem& _cameraSystem;
    InterfaceSystem& _interfaceSystem;

    Interface::Handle _interface;
    LabelWidget::Handle _cameraPositionLabel;
};

}
