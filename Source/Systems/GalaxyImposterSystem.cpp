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
    createCell(Vector3::Zero, 1000.0);
}

void GalaxyImposterSystem::adaptToObserver(Vector3 position, Quaternion rotation)
{
    (void)position;
    (void)rotation;
}

Entity::Iterator GalaxyImposterSystem::createCell(Vector3 localPosition, double size, Entity::Iterator parentCell)
{
    Entity& cell = scene().createEntity("GalaxyImposterCell");

    const Vector3 halfSize(size * 0.5);

    auto& transform = cell.addComponent<TransformComponent>();
    transform.localPosition = localPosition;

    auto& boundingBox = cell.addComponent<BoundingBoxComponent>();
    boundingBox.adaptive = false;
    boundingBox.localExtents = AxisAlignedBox(-halfSize, halfSize);

    auto& galaxyImposterCell = cell.addComponent<GalaxyImposterCellComponent>();

    cell.activate();
    if (parentCell)
    {
        auto& parentGalaxyImposterCell = parentCell->component<GalaxyImposterCellComponent>();
        galaxyImposterCell.depth = parentGalaxyImposterCell.depth + 1;

        parentCell->addChild(cell);
    }

    return cell.iterator();
}
