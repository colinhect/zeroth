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
#include <Scenes/ZerothScene.h>
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
    }

    virtual void tearDown() override
    {
    }
};
