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
class ZEROTH_EXPORT ObserverCameraSystem :
    public System<ObserverCameraSystem>,
    public EventListener<KeyboardEvent>,
    public EventListener<MouseEvent>
{
public:
    ObserverCameraSystem(Engine& engine, Scene& scene);

    void tickObservers(Seconds timeStep);

    /// \property{required}
    Path observerArchetype;

private:
    // Scene overrides
    void initialize() override;

    // EventListener overrides
    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const MouseEvent& event) override;

    Keyboard& _keyboard;
    Mouse& _mouse;

    Entity::Iterator _observerArchetype;
    Entity::Handle _activeObserver;
    Entity::Handle _lastActiveCamera;
};

}
