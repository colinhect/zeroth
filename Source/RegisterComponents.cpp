///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Graphics/Components/AmbientLight.h>
#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/Geometry.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/BoundingBox.h>
#include <Hect/Spacial/Components/Transform.h>

#include "Components/PlayerCamera.h"

using namespace hect;

void registerComponents()
{
    // Hect components
    Scene::registerComponent<AmbientLight>("AmbientLight");
    Scene::registerComponent<Camera>("Camera");
    Scene::registerComponent<DirectionalLight>("DirectionalLight");
    Scene::registerComponent<Geometry>("Geometry");
    Scene::registerComponent<RigidBody>("RigidBody");
    Scene::registerComponent<Transform>("Transform");
    Scene::registerComponent<BoundingBox>("BoundingBox");

    // Zeroth components
    Scene::registerComponent<PlayerCamera>("PlayerCamera");
}