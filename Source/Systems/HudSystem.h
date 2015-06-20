///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

namespace zeroth
{

/// \system
class HudSystem :
    public System<HudSystem>,
    public Listener<KeyboardEvent>
{
public:
    HudSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;
    void receiveEvent(const KeyboardEvent& event) override;

private:
    AssetCache& _assetCache;
    Keyboard& _keyboard;
    Mouse& _mouse;

    WidgetSystem::Handle _widgetSystem;
};

}