///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ProxyGalaxySystem.h"

#include "Components/SpiralGalaxy.h"

using namespace zeroth;

ProxyGalaxySystem::ProxyGalaxySystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _engine(engine),
    _assetCache(engine.assetCache())
{
}

void ProxyGalaxySystem::onComponentAdded(ProxyGalaxy::Iterator proxyGalaxy)
{
    Scene::Handle galaxyScene = _assetCache.getHandle<Scene>(baseGalaxyScene, _engine);

    CameraSystem::Handle cameraSystem = galaxyScene->system<CameraSystem>();
    if (cameraSystem)
    {
        Camera::Iterator activeCamera = cameraSystem->activeCamera();
        if (activeCamera)
        {
            Entity::Iterator galaxyEntity = galaxyScene->createEntity();
            galaxyEntity->setTransient(true);

            SpiralGalaxy::Iterator spiralGalaxy = galaxyEntity->addComponent<SpiralGalaxy>();
            spiralGalaxy->seed = proxyGalaxy->seed;

            galaxyEntity->activate();

            Transform::Iterator activeCameraTransform = activeCamera->entity()->component<Transform>();
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
                SkyBox::Iterator skyBox = skyBoxEntity->addComponent<SkyBox>();
                skyBox->texture = texture;
                skyBoxEntity->activate();

                // Create a light probe
                Entity::Iterator lightProbeEntity = scene().createEntity();
                LightProbe::Iterator lightProbe = lightProbeEntity->addComponent<LightProbe>();
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
        Camera::Iterator activeCamera = cameraSystem->activeCamera();
        if (activeCamera)
        {
            double factor = activeCamera->fieldOfView.degrees() / 90.0;
            resolution = static_cast<unsigned>(windowWidth * factor);
        }
    }

    return resolution;
}
