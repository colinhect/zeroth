///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2017 Colin Hill
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
    _observerEntity = entity.handle();
}

void IntergalacticScene::initialize()
{
    _galaxyImposterSystem.initialize();
    Scene::initialize();
}

void IntergalacticScene::tick(Seconds timeStep)
{
    _transformSystem.updateCommittedTransforms();

    if (_observerEntity)
    {
        auto& transform = _observerEntity->component<TransformComponent>();
        _galaxyImposterSystem.adaptToObserver(transform.globalPosition, transform.globalRotation);
    }

    refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}
