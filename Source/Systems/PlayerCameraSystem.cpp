///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlayerCameraSystem.h"

#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Spacial/Components/Transform.h>

PlayerCameraSystem::PlayerCameraSystem(Scene& scene) :
    System(scene),
    _viewX(&scene.inputSystem().axisWithName("viewX")),
    _viewY(&scene.inputSystem().axisWithName("viewY")),
    _moveX(&scene.inputSystem().axisWithName("moveX")),
    _moveY(&scene.inputSystem().axisWithName("moveY")),
    _roll(&scene.inputSystem().axisWithName("roll")),
    _speed(16)
{
    Mouse& mouse = scene.inputSystem().mouse();
    mouse.setMode(MouseMode_Relative);

    Keyboard& keyboard = scene.inputSystem().keyboard();
    keyboard.dispatcher().addListener(*this);
}

PlayerCameraSystem::~PlayerCameraSystem()
{
    Keyboard& keyboard = scene().inputSystem().keyboard();
    keyboard.dispatcher().removeListener(*this);
}

void PlayerCameraSystem::update(Real timeStep)
{
    for (PlayerCamera& playerCamera : scene().components<PlayerCamera>())
    {
        Entity& entity = playerCamera.entity();

        auto transform = entity.component<Transform>();
        if (transform)
        {
            auto camera = entity.component<Camera>();
            if (camera)
            {
                const Vector3& up = camera->up();
                const Vector3& right = camera->right();
                const Vector3& front = camera->front();

                Real rotateSpeed = timeStep * 50;
                Real rollSpeed = timeStep * 2;
                Real moveSpeed = timeStep * _speed;

                Mouse& mouse = scene().inputSystem().mouse();
                if (mouse.mode() == MouseMode_Relative)
                {
                    transform->rotate(up, _viewX->value() * rotateSpeed);
                    transform->rotate(right, _viewY->value() * -rotateSpeed);
                    transform->rotate(front, _roll->value() * -rollSpeed);
                }

                transform->translate(right * _moveX->value() * moveSpeed);
                transform->translate(front * _moveY->value() * moveSpeed);
            }
        }
    }
}

void PlayerCameraSystem::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType_KeyDown)
    {
        return;
    }

    if (event.key == Key_Tab)
    {
        Mouse& mouse = scene().inputSystem().mouse();
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