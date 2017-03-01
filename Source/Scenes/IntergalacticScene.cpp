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
    _galaxyImposterSystem(*this)
{
}

void IntergalacticScene::setObserver(Entity& entity)
{
    _observerEntity = entity.createHandle();
}

void IntergalacticScene::initialize()
{
    Scene::initialize();
}

void IntergalacticScene::tick(Seconds timeStep)
{
    _transformSystem.updateCommittedTransforms();

    if (_observerEntity)
    {
        auto transform = _observerEntity->component<TransformComponent>();
        if (transform)
        {
            _galaxyImposterSystem.adaptToObserver(transform->globalPosition, transform->globalRotation);
        }
    }

    refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}
