///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/Input/Systems/InputSystem.h>
#include <Hect/Runtime/Engine.h>

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds((Real)1 / (Real)60))
{
    engine.renderSystem().addWorld(_world);

    InputSystem& inputSystem = _world.system<InputSystem>();
    for (const JsonValue& axisValue : engine.settings()["inputAxes"])
    {
        InputAxis axis;
        axis.decodeFromJsonValue(axisValue);
        inputSystem.addAxis(axis);
    }

    AssetHandle<Data> worldData = engine.assetCache().getHandle<Data>("Test/World.world");
    _world.decodeFromData(*worldData, engine.assetCache());
}

ZerothGameMode::~ZerothGameMode()
{
    engine().renderSystem().removeWorld(_world);
}

void ZerothGameMode::tick()
{
    _world.tick(timeStep());
}