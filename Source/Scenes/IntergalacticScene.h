///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth._particleOctreeSystem
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

#include "Systems/GalaxyImposterSystem.h"

namespace zeroth
{

///
/// A scene of galaxies and the space inbetween at a scale of megaparsecs.
///
/// \scene
class ZEROTH_EXPORT IntergalacticScene :
    public Scene
{
public:
    IntergalacticScene(Engine& engine);

    void setObserver(Entity& entity);

    // Scene overrides
    virtual void initialize() override;
    virtual void tick(Seconds timeStep) override;
    virtual void render(RenderTarget& target) override;

private:
    BoundingBoxSystem _boundingBoxSystem;
    TransformSystem _transformSystem;
    GalaxyImposterSystem _galaxyImposterSystem;

    Entity::Handle _observerEntity;
};

}
