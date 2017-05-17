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
class ZEROTH_EXPORT StellarScene :
    public Scene
{
public:
    StellarScene(Engine& engine);

    // Scene overrides
    virtual void tick(Seconds timeStep) override;
    virtual void render(RenderTarget& target) override;
};

}
