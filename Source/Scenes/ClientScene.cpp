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

namespace
{
    const Path IntergalacticScenePath("Scenes/Intergalactic.scene");
}

ClientScene::ClientScene(Engine& engine) :
    Scene(engine),
    _interface_system(*this, engine.platform(), engine.renderer(), engine.vector_renderer()),
    _debug_system(*this, _interface_system),
    _input_system(*this, engine.platform(), engine.settings()),
    _camera_system(*this),
    _bounding_box_system(*this),
    _transform_system(*this, _bounding_box_system),
    _player_input_system(*this, _input_system, _transform_system, engine.platform()),
    //_intergalactic_scene(engine),
    //_interstellar_scene(engine),
    //_stellar_scene(engine),
    _scene_renderer(engine.asset_cache(), engine.task_pool())
{
    //_intergalactic_scene.load(IntergalacticScenePath);
}

void ClientScene::initialize()
{
    create_interface();
    _local_player_entity = entities().find_first_by_name("LocalPlayer");

    //_intergalactic_scene.set_observer(*_local_player_entity);
    //_intergalactic_scene.initialize();

    // Integrate content/asset generation from source files (from blender, YAML files, etc) to deserializable binary formats into the CMake build system.  Data is code, code is data... don't feel bad about hardcoding references to asset paths.  Write in Python, make extensible for adding any toolchain to the asset build process.  Could be a niche open source engine/framework for those who like manual control of a simple unified build system.

    Scene::initialize();
}

void ClientScene::tick(Seconds time_step)
{
    _input_system.update_axes(time_step);

    if (_local_player_entity)
    {
        //_player_input_system.handle_player_input(time_step, *_local_player_entity);
    }

    //_intergalactic_scene.tick(time_step);
    //_interstellar_scene.tick(time_step);
    //_stellar_scene.tick(time_step);

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

void ClientScene::create_interface()
{
    Window& main_window = engine().main_window();
    _interface = _interface_system.create_interface(main_window);

    LabelWidget::Handle label = _interface->create_child<LabelWidget>();
    label->set_text("Testing... One two three and stuff");
}
