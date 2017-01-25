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
    _boundingBoxSystem(createSystem<BoundingBoxSystem>()),
    _cameraSystem(createSystem<CameraSystem>()),
    _transformSystem(createSystem<TransformSystem>()),
    _renderSystem(createSystem<RenderSystem>())
{
}

void IntergalacticScene::initialize()
{
    Scene::initialize();
}

void IntergalacticScene::tick(Seconds timeStep)
{
    Scene::refresh();

    _transformSystem.updateCommittedTransforms();
    _cameraSystem.updateAllCameras();

    Scene::refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}

