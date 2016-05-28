///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ChaseCameraSystem.h"

#include "Components/ChaseCamera.h"

using namespace zeroth;

ChaseCameraSystem::ChaseCameraSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void ChaseCameraSystem::tick(double timeStep)
{
    (void)timeStep;
}