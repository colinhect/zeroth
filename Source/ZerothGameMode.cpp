///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothGameMode.h"

#include <Hect/IO/JsonDecoder.h>
#include <Hect/Logic/Systems/InputSystem.h>
#include <Hect/Runtime/Engine.h>

using namespace zeroth;

ZerothGameMode::ZerothGameMode(Engine& engine) :
    GameMode(engine, TimeSpan::fromSeconds((Real)1 / (Real)60))
{
    engine.renderSystem().addWorld(_world);

    InputSystem& inputSystem = _world.system<InputSystem>();
    for (const JsonValue& axisValue : engine.config()["inputAxes"])
    {
        InputAxis axis;

        JsonDecoder decoder(axisValue);
        decoder >> decodeValue(axis);

        inputSystem.addAxis(axis);
    }

    AssetCache::SelectDirectoryScope scope(engine.assetCache(), "Zeroth/Test");

    AssetHandle<JsonValue> worldJsonValue = engine.assetCache().getHandle<JsonValue>("World.world");
    JsonDecoder decoder(*worldJsonValue, engine.assetCache());
    decoder >> beginObject() >> decodeValue(_world) >> endObject();
}

ZerothGameMode::~ZerothGameMode()
{
    engine().renderSystem().removeWorld(_world);
}

void ZerothGameMode::tick()
{
    _world.tick(timeStep());
}