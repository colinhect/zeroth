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
#include "ClientScene.h"

using namespace zeroth;

ClientScene::ClientScene(Engine& engine) :
    Scene(engine),
    _interface_system(*this, engine.asset_cache(), engine.platform(), engine.renderer(), engine.vector_renderer()),
    _debug_system(*this, engine.asset_cache(), _interface_system),
    _input_system(*this, engine.platform(), engine.settings()),
    _camera_system(*this),
    _bounding_box_system(*this),
    _transform_system(*this, _bounding_box_system),
    _player_input_system(*this, _input_system, _transform_system, engine.platform()),
    _stellar_scene(engine),
    _hud_system(*this, _stellar_scene, _interface_system, engine.main_window()),
    _scene_renderer(engine.asset_cache(), engine.task_pool())
{
}

void ClientScene::initialize()
{
    _stellar_scene.initialize();

    Scene::initialize();
}

void ClientScene::tick(Seconds time_step)
{
    _hud_system.update_widgets();

    _input_system.update_axes(time_step);

    if (_local_player_entity)
    {
        //_player_input_system.handle_player_input(time_step, *_local_player_entity);
    }

    //_intergalactic_scene.tick(time_step);
    //_interstellar_scene.tick(time_step);
    _stellar_scene.tick(time_step);

    _transform_system.update_committed_transforms();
    _camera_system.update_all_cameras();

    _interface_system.tick_all_interfaces(time_step);

    refresh();
}

void ClientScene::render(RenderTarget& target)
{
    Renderer& renderer = engine().renderer();

    //_scene_renderer.render(_intergalactic_scene, _camera_system, renderer, target);
    _scene_renderer.render(*this, _camera_system, renderer, target);

    _interface_system.render_all_interfaces();
}

StellarScene& ClientScene::stellar_scene()
{
    return _stellar_scene;
}
