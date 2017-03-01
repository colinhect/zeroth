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

    void adaptToObserver(const Vector3& position, const Quaternion& rotation);

private:
    std::vector<Entity::Handle> _rootCellEntities;
};

}
