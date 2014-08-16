///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Logic/ComponentRegistry.h>
#include <Hect/Logic/GameModeRegistry.h>
#include <Hect/Platform/Platform.h>
#include <Hect/Runtime/Engine.h>


#include <Hect/Graphics/Components/Camera.h>
#include <Hect/Graphics/Components/DirectionalLight.h>
#include <Hect/Graphics/Components/LightProbe.h>
#include <Hect/Graphics/Components/Model.h>
#include <Hect/Graphics/Components/SkyBox.h>
#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Logic/GameMode.h>
#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Physics/Systems/PhysicsSystem.h>
#include <Hect/Runtime/Engine.h>
#include <Hect/Spacial/Components/BoundingBox.h>
#include <Hect/Spacial/Components/Transform.h>
#include <Hect/Spacial/Systems/BoundingBoxSystem.h>
#include <Hect/Spacial/Systems/TransformSystem.h>

#include "Components/CockpitCamera.h"
#include "Components/PlayerCamera.h"
#include "Components/PlayerShipControl.h"
#include "Components/Ship.h"
#include "Components/Thruster.h"
#include "Systems/CockpitCameraSystem.h"
#include "Systems/PlayerCameraSystem.h"
#include "Systems/PlayerShipControlSystem.h"

using namespace hect;

#include "ZerothGameMode.h"

#ifdef HECT_WINDOWS_BUILD
#ifdef HECT_DEBUG_BUILD
#include <vld.h>
#endif
#endif

int main(int argc, const char* argv[])
{
    try
    {
        GameModeRegistry::registerType<ZerothGameMode>();

        ComponentRegistry::registerType<BoundingBox>();
        ComponentRegistry::registerType<Camera>();
        ComponentRegistry::registerType<DirectionalLight>();
        ComponentRegistry::registerType<LightProbe>();
        ComponentRegistry::registerType<Model>();
        ComponentRegistry::registerType<RigidBody>();
        ComponentRegistry::registerType<SkyBox>();
        ComponentRegistry::registerType<Transform>();
        //
        ComponentRegistry::registerType<CockpitCamera>();
        ComponentRegistry::registerType<PlayerCamera>();
        ComponentRegistry::registerType<PlayerShipControl>();
        ComponentRegistry::registerType<Ship>();
        ComponentRegistry::registerType<Thruster>();

        Engine engine(argc, argv);
        return engine.main();
    }
    catch (Error& error)
    {
        HECT_ERROR(error.what());
        Platform::showFatalError(error.what());
    }

    return 0;
}