///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ProxyGalaxySystem.h"

#include "Components/SpiralGalaxyComponent.h"
#include "Scenes/ZerothScene.h"

using namespace zeroth;

ProxyGalaxySystem::ProxyGalaxySystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void ProxyGalaxySystem::onComponentAdded(ProxyGalaxyComponent::Iterator proxyGalaxy)
{
    AssetCache& assetCache = engine().assetCache();
    auto galaxyScene = assetCache.getHandle<ZerothScene>(baseGalaxyScene, engine());

    CameraSystem& cameraSystem = galaxyScene->system<CameraSystem>();
    CameraComponent::Iterator activeCamera = cameraSystem.activeCamera();
    if (activeCamera)
    {
        Entity::Iterator galaxyEntity = galaxyScene->createEntity();
        galaxyEntity->setTransient(true);

        SpiralGalaxyComponent::Iterator spiralGalaxy = galaxyEntity->addComponent<SpiralGalaxyComponent>();
        spiralGalaxy->seed = proxyGalaxy->seed;

        galaxyEntity->activate();

        TransformComponent::Iterator activeCameraTransform = activeCamera->entity()->component<TransformComponent>();
        if (activeCameraTransform)
        {
            activeCameraTransform->globalPosition = proxyGalaxy->position;
        }

        // Tick the scene to insure that the galaxy has adapted to the camera
        galaxyScene->tick(0.0);
        galaxyScene->tick(0.0); // Issue #186

        // Render the scene to a cubic texture
        RenderSystem& renderSystem = galaxyScene->system<RenderSystem>();

        unsigned skyBoxResolution = computeSkyBoxResolution();
        TextureCube::Handle texture(new TextureCube("ProxyGalaxySkyBox", skyBoxResolution, skyBoxResolution));
        texture->setPixelFormat(PixelFormat::Rgb16);
        renderSystem.renderToTextureCube(scene(), proxyGalaxy->position, *texture);

        // Create a sky box
        Entity::Iterator skyBoxEntity = scene().createEntity();
        SkyBoxComponent::Iterator skyBox = skyBoxEntity->addComponent<SkyBoxComponent>();
        skyBox->texture = texture;
        skyBoxEntity->activate();

        // Create a light probe
        Entity::Iterator lightProbeEntity = scene().createEntity();
        LightProbeComponent::Iterator lightProbe = lightProbeEntity->addComponent<LightProbeComponent>();
        lightProbe->texture = texture;
        lightProbeEntity->activate();
    }

    assetCache.remove(galaxyScene);
}

unsigned ProxyGalaxySystem::computeSkyBoxResolution()
{
    unsigned windowWidth = engine().window().width();

    unsigned resolution = windowWidth;

    auto& cameraSystem = scene().system<CameraSystem>();
    CameraComponent::Iterator activeCamera = cameraSystem.activeCamera();
    if (activeCamera)
    {
        double factor = activeCamera->fieldOfView.inDegrees() / 90.0;
        resolution = static_cast<unsigned>(windowWidth * factor);
    }

    return resolution;
}
