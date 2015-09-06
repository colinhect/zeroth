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
    public System<ObserverCameraSystem>,
    public Listener<KeyboardEvent>,
    public Listener<MouseEvent>
{
public:
    ObserverCameraSystem(Engine& engine, Scene& scene);

    void tick(double timeStep) override;

    void receiveEvent(const KeyboardEvent& event) override;
    void receiveEvent(const MouseEvent& event) override;

private:
    Mouse& _mouse;

    CameraSystem::Handle _cameraSystem;
    TransformSystem::Handle _transformSystem;
    InputSystem::Handle _inputSystem;

    Entity::Iterator _observerEntity;
    Entity::Handle _activeObserver;
    Entity::Handle _lastActiveCamera;
};

}