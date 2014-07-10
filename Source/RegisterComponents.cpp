///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Logic/Scene.h>
#include <Hect/Logic/Components/AmbientLight.h>
#include <Hect/Logic/Components/BoundingBox.h>
#include <Hect/Logic/Components/Camera.h>
#include <Hect/Logic/Components/DirectionalLight.h>
#include <Hect/Logic/Components/Geometry.h>
#include <Hect/Logic/Components/RigidBody.h>
#include <Hect/Logic/Components/Transform.h>

#include "Components/PlayerCamera.h"

using namespace hect;

void registerComponents()
{
    // Hect components
    Scene::registerComponent<AmbientLight>("AmbientLight");
    Scene::registerComponent<DirectionalLight>("DirectionalLight");
    Scene::registerComponent<Camera>("Camera");
    Scene::registerComponent<Geometry>("Geometry");
    Scene::registerComponent<Transform>("Transform");
    Scene::registerComponent<BoundingBox>("BoundingBox");
    Scene::registerComponent<RigidBody>("RigidBody");

    // Zeroth components
    Scene::registerComponent<PlayerCamera>("PlayerCamera");
}