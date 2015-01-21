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
class ObserverCameraSystem :
    public System<>,
    public Listener<KeyboardEvent>
{
public:
    ObserverCameraSystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;

    void receiveEvent(const KeyboardEvent& event) override;

private:
    Entity::Iterator _observerEntity;
    Entity::Handle _activeObserver;
    Entity::Handle _lastActiveCamera;
};

}