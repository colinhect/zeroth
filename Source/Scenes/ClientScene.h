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

#include "Scenes/IntergalacticScene.h"
#include "Scenes/InterstellarScene.h"
#include "Scenes/StellarScene.h"

namespace zeroth
{

/// \scene
class ZEROTH_EXPORT ClientScene :
    public Scene
{
public:
    ClientScene(Engine& engine);

    // Scene overrides
    virtual void initialize() override;
    virtual void tick(Seconds timeStep) override;
    virtual void render(RenderTarget& target) override;

private:
    void createInterface();

    InterfaceSystem _interfaceSystem;
    DebugSystem _debugSystem;
    InputSystem _inputSystem;
    CameraSystem _cameraSystem;
    RenderSystem _renderSystem;

    IntergalacticScene _intergalacticScene;
    InterstellarScene _interstellarScene;
    StellarScene _stellarScene;

    Interface::Handle _interface;
};

}
