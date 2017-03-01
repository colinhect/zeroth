///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxyImposterSystem.h"

using namespace zeroth;

GalaxyImposterSystem::GalaxyImposterSystem(Scene& scene) :
    System(scene)
{
}

void GalaxyImposterSystem::adaptToObserver(const Vector3& position, const Quaternion& rotation)
{
    (void)position;
    (void)rotation;
}
