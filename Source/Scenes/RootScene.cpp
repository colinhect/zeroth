///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "RootScene.h"

using namespace zeroth;

RootScene::RootScene(Engine& engine) :
    Scene(engine),
    _renderSystem(createSystem<RenderSystem>())
{
}

void RootScene::tick(Seconds timeStep)
{
    (void)timeStep;
}

void RootScene::render(RenderTarget& target)
{
    (void)target;
}
