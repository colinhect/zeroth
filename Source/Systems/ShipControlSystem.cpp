///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ShipControlSystem.h"

#include <Hect/Logic/World.h>
#include <Hect/Logic/Components/RigidBody.h>
#include <Hect/Logic/Systems/PhysicsSystem.h>
#include <Hect/Logic/Components/Transform.h>

#include "Components/Thruster.h"

ShipControlSystem::ShipControlSystem(World& world) :
    System(world)
{
}

void ShipControlSystem::controlShip(Entity& ship, const Vector3& angularAmount, Real thrustAmount, Real timeStep)
{
    PhysicsSystem& physicsSystem = world().system<PhysicsSystem>();

    auto transform = ship.component<Transform>();
    if (transform)
    {
        auto rigidBody = ship.component<RigidBody>();
        if (rigidBody)
        {
            {
                Vector3 angularVelocity = rigidBody->angularVelocity;
                angularVelocity = angularVelocity - angularVelocity * timeStep * 1.0;

                Vector3 angularDelta = transform->globalRotation * angularAmount;
                angularDelta *= timeStep * 2.0;

                physicsSystem.setAngularVelocity(*rigidBody, angularVelocity + angularDelta);
            }
            {
                Vector3 linearVelocity = rigidBody->linearVelocity;
                linearVelocity = linearVelocity - linearVelocity * timeStep * 0.5;
                physicsSystem.setLinearVelocity(*rigidBody, linearVelocity);

                auto thrusterEntities = ship.findDescendants([](const Entity& entity)
                {
                    return entity.component<Thruster>();
                });

                for (auto thrusterEntity : thrusterEntities)
                {
                    auto thruster = thrusterEntity->component<Thruster>();
                    if (thruster)
                    {
                        auto thrusterTransform = thrusterEntity->component<Transform>();
                        if (thrusterTransform)
                        {
                            Vector3 thrustVector = transform->globalRotation * thruster->direction;
                            thrustVector = thrustVector.normalized() * thruster->power * thrustAmount;

                            physicsSystem.applyForce(*rigidBody, thrustVector, Vector3::zero());
                        }
                    }
                }
            }
        }
    }
}