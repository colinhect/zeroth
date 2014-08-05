///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Application.h>
#include <Hect/Core/Uncopyable.h>
#include <Hect/Event/Listener.h>
#include <Hect/Logic/Loop.h>
#include <Hect/Logic/Scene.h>

#include "OrbitScene.h"

using namespace hect;

class MainLoop :
    public Loop,
    public Listener<KeyboardEvent>,
    public Uncopyable
{
public:
    MainLoop(Input& input, Storage& storage, Renderer& renderer, RenderTarget& renderTarget);
    ~MainLoop();

    void fixedUpdate(Real timeStep);
    void frameUpdate(Real delta);

    void receiveEvent(const KeyboardEvent& event);

private:
    Input* _input;
    RenderTarget* _renderTarget;

    AssetCache _assetCache;
    OrbitScene _scene;
};