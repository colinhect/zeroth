///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT GalaxyImposterSystem :
    public System<GalaxyImposterSystem>
{
public:
    GalaxyImposterSystem(Scene& scene);

    void initialize();

    void adaptToObserver(Vector3 position, Quaternion rotation);

private:
    Entity::Iterator createCell(Vector3 localPosition, double size, Entity::Iterator parentCell = Entity::Iterator());

    std::vector<Entity::Handle> _rootCells;

    // The maximum visibility distance; set to the radius of the obserable
    // universe in megaparsecs
    const double _maxVisibilityDistance { 14000.0 };

    const double _rootCellSize { 1000.0 };
};

}
