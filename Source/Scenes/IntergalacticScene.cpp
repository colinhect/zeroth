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
    _bounding_box_system(*this),
    _transform_system(*this, _bounding_box_system),
    _galaxy_imposter_system(*this)
{
}

void IntergalacticScene::set_observer(Entity& entity)
{
    _observer_entity = entity.handle();
}

void IntergalacticScene::initialize()
{
    _galaxy_imposter_system.initialize();
    Scene::initialize();
}

void IntergalacticScene::tick(Seconds time_step)
{
    _transform_system.update_committed_transforms();

    if (_observer_entity)
    {
        auto& transform = _observer_entity->component<TransformComponent>();
        _galaxy_imposter_system.adapt_to_observer(transform.global_position, transform.global_rotation);
    }

    refresh();
}

void IntergalacticScene::render(RenderTarget& target)
{
    (void)target;
}
