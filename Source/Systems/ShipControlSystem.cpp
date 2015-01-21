///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ShipControlSystem.h"

#include "Components/Thruster.h"

using namespace zeroth;

ShipControlSystem::ShipControlSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void ShipControlSystem::controlShip(Entity& ship, const Vector3& angularAmount, double thrustAmount, double timeStep)
{
    PhysicsSystem& physicsSystem = scene().system<PhysicsSystem>();
    TransformSystem& transformSystem = scene().system<TransformSystem>();

    auto transform = ship.component<Transform>();
    if (transform)
    {
        auto rigidBody = ship.component<RigidBody>();
        if (rigidBody)
        {
            Vector3 angularVelocity = rigidBody->angularVelocity;
            Vector3 linearVelocity = rigidBody->linearVelocity;

            // Apply friction to angular velocity
            angularVelocity = angularVelocity - angularVelocity * timeStep * 1.0;

            // Compute angular velocity delta based on control amount
            Vector3 angularDelta = transform->globalRotation * angularAmount;
            angularDelta *= timeStep * 2.0;

            // Apply fiction to linear velocity
            linearVelocity = linearVelocity - linearVelocity * timeStep * 0.5;

            // Update the rigidy body based on new linear and angular velocities
            rigidBody->angularVelocity = angularVelocity + angularDelta;
            rigidBody->linearVelocity = linearVelocity;
            physicsSystem.commit(*rigidBody);

            // Find all child entities that are thrusters
            auto thrusterEntities = ship.findDescendants([](const Entity& entity)
            {
                return entity.component<Thruster>();
            });

            // Apply force from all thrusters
            for (auto thrusterEntity : thrusterEntities)
            {
                Thruster& thruster = *thrusterEntity->component<Thruster>();
                auto thrusterTransform = thrusterEntity->component<Transform>();
                if (thrusterTransform)
                {
                    Vector3 thrustVector = transform->globalRotation * thruster.direction;
                    thrustVector = thrustVector.normalized() * thruster.power * thrustAmount;

                    physicsSystem.applyForce(*rigidBody, thrustVector, Vector3::zero());
                }
            }
        }
    }
}