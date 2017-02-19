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
    _boundingBoxSystem(engine, *this),
    _transformSystem(engine, *this, _boundingBoxSystem)
{
}

void IntergalacticScene::initialize()
{

    Scene::initialize();
}

void IntergalacticScene::tick(Seconds timeStep)
{
    _transformSystem.updateCommittedTransforms();
    //_cameraSystem.updateAllCameras();

    refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}

