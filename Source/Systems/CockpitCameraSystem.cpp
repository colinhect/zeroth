///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "CockpitCameraSystem.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Spacial/Components/Transform.h>

CockpitCameraSystem::CockpitCameraSystem(Scene& scene, InputSystem& inputSystem) :
    System(scene),
    _inputSystem(&inputSystem),
    _viewX(&inputSystem.axisWithName("viewX")),
    _viewY(&inputSystem.axisWithName("viewY"))
{
    _inputSystem->mouse().setMode(MouseMode_Relative);

    Keyboard& keyboard = _inputSystem->keyboard();
    keyboard.dispatcher().addListener(*this);
}

CockpitCameraSystem::~CockpitCameraSystem()
{
    Keyboard& keyboard = _inputSystem->keyboard();
    keyboard.dispatcher().removeListener(*this);
}

void CockpitCameraSystem::update(Real timeStep)
{
    for (CockpitCamera& cockpitCamera : scene().components<CockpitCamera>())
    {
        Entity& entity = cockpitCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                /*
                const Vector3& up = camera->up();
                const Vector3& right = camera->right();

                Real rotateSpeed = timeStep * 50;

                if (_inputSystem->mouse().mode() == MouseMode_Relative)
                {
                    transform->rotate(Vector3::unitY(), _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                }
                */
            }
        }
    }
}

void CockpitCameraSystem::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType_KeyDown)
    {
        return;
    }

    if (event.key == Key_Tab)
    {
        Mouse& mouse = _inputSystem->mouse();
        if (mouse.mode() == MouseMode_Cursor)
        {
            mouse.setMode(MouseMode_Relative);
        }
        else
        {
            mouse.setMode(MouseMode_Cursor);
        }
    }
}