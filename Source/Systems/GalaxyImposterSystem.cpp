///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
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
