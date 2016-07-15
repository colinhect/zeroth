///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <celero/Celero.h>

#include <Hect.h>
using namespace hect;

#include <Components/PlanetComponent.h>
#include <Components/PlanetPatchComponent.h>
#include <Systems/PlanetSystem.h>
using namespace zeroth;

class PlanetTestFixture :
    public celero::TestFixture
{
public:
    PlanetTestFixture()
    {
    }

    void setUp(int64_t experimentValue) override
    {
        (void)experimentValue;

        Engine& engine = Engine::instance();
        AssetCache& assetCache = engine.assetCache();

        // Clear all cached assets, forcing all assets to be re-loaded
        assetCache.clear();

        // Load a blank scene
        scene = assetCache.getHandle<Scene>("Hect/Scenes/Default.scene", engine);

        // Add planet components and system to the scene
        scene->addComponentType<PlanetComponent>();
        scene->addComponentType<PlanetPatchComponent>();
        scene->addSystemType<PlanetSystem>();

        // Get a handle to the planet system
        planetSystem = scene->system<PlanetSystem>();

        // Create the planet entity
        planetEntity = scene->createEntity();
        planet = planetEntity->addComponent<PlanetComponent>();
        planet->name = "Test";
        planet->meanRadius = 100.0;

        // Refresh the scene
        scene->refresh();
    }

    virtual void tearDown() override
    {
        scene.invalidate();
        planetSystem.invalidate();
        planetEntity.invalidate();
        planet.invalidate();
    }

    Scene::Handle scene;
    PlanetSystem::Handle planetSystem;
    Entity::Iterator planetEntity;
    PlanetComponent::Iterator planet;
};

BASELINE_F(PlanetTests, AdaptPlanetAtSurface, PlanetTestFixture, 10, 10)
{
    // Adapt the planet as if the camera is directly at the surface
    planetSystem->adapt(Vector3::UnitX * planet->meanRadius, planetEntity);

    // Adapt the planet as if the camera is far away from the surface
    planetSystem->adapt(Vector3::One * 10000.0, planetEntity);
}

BENCHMARK_F(PlanetTests, AdaptPlanetCloseToSurface, PlanetTestFixture, 10, 10)
{
    // Adapt the planet as if the camera is directly at the surface
    planetSystem->adapt(Vector3::UnitX * planet->meanRadius * 1.5, planetEntity);

    // Adapt the planet as if the camera is far away from the surface
    planetSystem->adapt(Vector3::One * 10000.0, planetEntity);
}
