///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/LightProbe.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Logic/Scene.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/BoundingBox.h>
#include <Hect/Spacial/Components/Transform.h>

#include "Components/PlayerCamera.h"

using namespace hect;

void registerComponents(Scene& scene)
{
    // Hect components
    scene.registerComponent<Camera>("Camera");
    scene.registerComponent<DirectionalLight>("DirectionalLight");
    scene.registerComponent<LightProbe>("LightProbe");
    scene.registerComponent<Model>("Model");
    scene.registerComponent<SkyBox>("SkyBox");
    scene.registerComponent<RigidBody>("RigidBody");
    scene.registerComponent<Transform>("Transform");
    scene.registerComponent<BoundingBox>("BoundingBox");

    // Zeroth components
    scene.registerComponent<PlayerCamera>("PlayerCamera");
}