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

/// \scene
class ZEROTH_EXPORT IntergalacticScene :
    public Scene
{
public:
    IntergalacticScene(Engine& engine);

    // Scene overrides
    virtual void initialize() override;
    virtual void tick(Seconds timeStep) override;
    virtual void render(RenderTarget& target) override;

private:
    BoundingBoxSystem& _boundingBoxSystem;
    CameraSystem& _cameraSystem;
    TransformSystem& _transformSystem;
};

}
