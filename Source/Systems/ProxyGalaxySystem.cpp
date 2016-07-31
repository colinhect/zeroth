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
    System(engine, scene),
    _engine(engine),
    _assetCache(engine.assetCache())
{
}

void ProxyGalaxySystem::onComponentAdded(ProxyGalaxyComponent::Iterator proxyGalaxy)
{
    auto galaxyScene = _assetCache.getHandle<ZerothScene>(baseGalaxyScene, _engine);

    CameraSystem::Handle cameraSystem = galaxyScene->system<CameraSystem>();
    if (cameraSystem)
    {
        CameraComponent::Iterator activeCamera = cameraSystem->activeCamera();
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
            RenderSystem::Handle renderSystem = galaxyScene->system<RenderSystem>();
            if (renderSystem)
            {
                unsigned skyBoxResolution = computeSkyBoxResolution();
                TextureCube::Handle texture(new TextureCube("ProxyGalaxySkyBox", skyBoxResolution, skyBoxResolution, PixelFormat::Rgb16));
                renderSystem->renderToTextureCube(proxyGalaxy->position, *texture);

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
        }
    }

    _assetCache.remove(galaxyScene);
}

unsigned ProxyGalaxySystem::computeSkyBoxResolution()
{
    unsigned windowWidth = _engine.window().width();

    unsigned resolution = windowWidth;

    CameraSystem::Handle cameraSystem = scene().system<CameraSystem>();
    if (cameraSystem)
    {
        CameraComponent::Iterator activeCamera = cameraSystem->activeCamera();
        if (activeCamera)
        {
            double factor = activeCamera->fieldOfView.inDegrees() / 90.0;
            resolution = static_cast<unsigned>(windowWidth * factor);
        }
    }

    return resolution;
}
