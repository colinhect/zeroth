///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "IntergalacticScene.h"

using namespace zeroth;

IntergalacticScene::IntergalacticScene(Engine& engine) :
    Scene(engine),
    _boundingBoxSystem(*this),
    _transformSystem(*this, _boundingBoxSystem),
    _particleOctreeSystem(*this)
{
}

void IntergalacticScene::initialize()
{
    Scene::initialize();
}

void IntergalacticScene::tick(Seconds timeStep)
{
    _transformSystem.updateCommittedTransforms();

    refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}
