///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ShipControlSystem.h"

#include <Hect/Physics/Components/RigidBody.h>
#include <Hect/Spacial/Components/Transform.h>

#include "Components/Thruster.h"

ShipControlSystem::ShipControlSystem(Scene& scene, PhysicsSystem& physicsSystem) :
    System(scene),
    _physicsSystem(&physicsSystem)
{
}

ShipControlSystem::~ShipControlSystem()
{
}

void ShipControlSystem::controlShip(Entity& ship, const Vector3& angularAmount, Real thrustAmount, Real timeStep)
{
    auto transform = ship.component<Transform>();
    if (transform)
    {
        auto rigidBody = ship.component<RigidBody>();
        if (rigidBody)
        {
            {
                Vector3 angularVelocity = rigidBody->angularVelocity();

                Vector3 angularDelta = transform->globalRotation() * angularAmount;
                angularDelta *= timeStep;

                rigidBody->setAngularVelocity((angularVelocity + angularDelta) * 0.99);
            }
            {
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
                            Vector3 thrustVector = transform->globalRotation() * thruster->direction;
                            thrustVector = thrustVector.normalized() * thruster->power * thrustAmount;

                            _physicsSystem->applyForce(*rigidBody, thrustVector, Vector3::zero());
                        }
                    }
                }
            }
        }
    }
}