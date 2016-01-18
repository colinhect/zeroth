///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ShipControlSystem.h"

#include "Components/Thruster.h"

using namespace zeroth;

ShipControlSystem::ShipControlSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _transformSystem(scene.system<TransformSystem>()),
    _physicsSystem(scene.system<PhysicsSystem>())
{
}

void ShipControlSystem::controlShip(Entity& ship, const Vector3& directionalThrust, const Vector3& angularThrust, double timeStep)
{
    if (_transformSystem && _physicsSystem)
    {
        Transform::Iterator transform = ship.component<Transform>();
        if (transform)
        {
            RigidBody::Iterator rigidBody = ship.component<RigidBody>();
            if (rigidBody)
            {
                Vector3 angularVelocity = rigidBody->angularVelocity;
                Vector3 linearVelocity = rigidBody->linearVelocity;

                // Apply friction to angular velocity
                angularVelocity = angularVelocity - angularVelocity * timeStep * 1.0;

                // Compute angular velocity delta based on control amount
                Vector3 angularDelta = transform->globalRotation * angularThrust;
                angularDelta *= timeStep * 2.0;

                // Apply fiction to linear velocity
                linearVelocity = linearVelocity - linearVelocity * timeStep * 0.5;

                // Update the rigidy body based on new linear and angular velocities
                rigidBody->angularVelocity = angularVelocity + angularDelta;
                rigidBody->linearVelocity = linearVelocity;
                _physicsSystem->commit(*rigidBody);

                // Find all child entities that are thrusters
                auto thrusterEntities = ship.findDescendants([](const Entity& entity)
                {
                    Thruster::ConstIterator thruster = entity.component<Thruster>();
                    return thruster && thruster->type == ThrusterType::PrimaryEngine;
                });

                // Apply force from all thrusters
                for (Entity::Iterator thrusterEntity : thrusterEntities)
                {
                    Thruster::Iterator thruster = thrusterEntity->component<Thruster>();
                    Transform::Iterator thrusterTransform = thrusterEntity->component<Transform>();
                    if (thrusterTransform)
                    {
                        Vector3 thrustVector = transform->globalRotation * directionalThrust * thruster->power * timeStep;
                        _physicsSystem->applyForce(*rigidBody, thrustVector, Vector3::Zero);
                    }
                }
            }
        }
    }
}