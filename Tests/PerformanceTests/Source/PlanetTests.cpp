///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <celero/Celero.h>

#include <Hect.h>
using namespace hect;

#include <Systems/PlanetSystem.h>
using namespace zeroth;

class PlanetTestFixture :
    public celero::TestFixture
{
public:
    PlanetTestFixture()
    {
        Engine& engine = Engine::instance();
        AssetCache& assetCache = engine.assetCache();

        scene = assetCache.getHandle<Scene>("Scenes/Base/Planetary.scene", engine);
    }

    void setUp(int64_t experimentValue) override
    {
    }

    virtual void tearDown() override
    {
    }

    Scene::Handle scene;
};

BASELINE_F(SortRandInts, BubbleSort, PlanetTestFixture, 5, 1)
{
    PlanetSystem::Handle planetSystem = scene->system<PlanetSystem>();
}
