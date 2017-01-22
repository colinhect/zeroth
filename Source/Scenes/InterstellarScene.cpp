///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "InterstellarScene.h"

using namespace zeroth;

InterstellarScene::InterstellarScene(Engine& engine) :
    Scene(engine)
{
}

void InterstellarScene::tick(Seconds timeStep)
{
    (void)timeStep;
}

void InterstellarScene::render(RenderTarget& target)
{
    (void)target;
}
