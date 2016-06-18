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
    public Listener<KeyboardEvent>,
    public Listener<MouseEvent>
{
public:
    ObserverCameraSystem(Engine& engine, Scene& scene);

    void initialize() override;
    void tick(double timeStep) override;

    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const MouseEvent& event) override;

    /// \property{required}
    Path observerArchetype;

private:
    Mouse& _mouse;

    CameraSystem::Handle _cameraSystem;
    TransformSystem::Handle _transformSystem;
    InputSystem::Handle _inputSystem;

    Entity::Iterator _observerArchetype;
    Entity::Handle _activeObserver;
    Entity::Handle _lastActiveCamera;
};

}
