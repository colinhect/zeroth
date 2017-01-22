///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "StellarScene.h"

using namespace zeroth;

StellarScene::StellarScene(Engine& engine) :
    Scene(engine)
{
}

void StellarScene::tick(Seconds timeStep)
{
    (void)timeStep;
}

void StellarScene::render(RenderTarget& target)
{
    (void)target;
}
