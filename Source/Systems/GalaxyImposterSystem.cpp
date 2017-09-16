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
#include "GalaxyImposterSystem.h"

#include "Components/GalaxyImposterCellComponent.h"

using namespace zeroth;

GalaxyImposterSystem::GalaxyImposterSystem(Scene& scene) :
    System(scene)
{
}

void GalaxyImposterSystem::initialize()
{
    create_cell(Vector3::Zero, 1000.0);
}

void GalaxyImposterSystem::adapt_to_observer(Vector3 position, Quaternion rotation)
{
    (void)position;
    (void)rotation;
}

Entity::Iterator GalaxyImposterSystem::create_cell(Vector3 local_position, double size, Entity::Iterator parent_cell)
{
    Entity& cell = scene().create_entity("GalaxyImposterCell");

    const Vector3 half_size(size * 0.5);

    auto& transform = cell.add_component<TransformComponent>();
    transform.local_position = local_position;

    auto& bounding_box = cell.add_component<BoundingBoxComponent>();
    bounding_box.adaptive = false;
    bounding_box.local_extents = AxisAlignedBox(-half_size, half_size);

    auto& galaxy_imposter_cell = cell.add_component<GalaxyImposterCellComponent>();

    cell.activate();
    if (parent_cell)
    {
        auto& parent_galaxy_imposter_cell = parent_cell->component<GalaxyImposterCellComponent>();
        galaxy_imposter_cell.depth = parent_galaxy_imposter_cell.depth + 1;

        parent_cell->add_child(cell);
    }

    return cell.iterator();
}
