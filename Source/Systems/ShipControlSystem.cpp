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
    _debugSystem(scene.system<DebugSystem>()),
    _transformSystem(scene.system<TransformSystem>()),
    _physicsSystem(scene.system<PhysicsSystem>())
{
}

void ShipControlSystem::controlShip(Entity& ship, const Vector3& directionalThrust, const Vector3& angularThrust, double timeStep)
{
    if (_transformSystem && _physicsSystem)
    {
        Transform::Iterator shipTransform = ship.component<Transform>();
        if (shipTransform)
        {
            RigidBody::Iterator shipRigidBody = ship.component<RigidBody>();
            if (shipRigidBody)
            {
                Vector3 angularVelocity = shipRigidBody->angularVelocity;
                Vector3 linearVelocity = shipRigidBody->linearVelocity;

                // Apply friction to angular velocity
                angularVelocity = angularVelocity - angularVelocity * timeStep * 1.0;

                // Compute angular velocity delta based on control amount
                Vector3 angularDelta = shipTransform->globalRotation * angularThrust;
                angularDelta *= timeStep * 2.0;

                // Apply fiction to linear velocity
                linearVelocity = linearVelocity - linearVelocity * timeStep * 0.5;

                // Update the rigidy body based on new linear and angular velocities
                shipRigidBody->angularVelocity = angularVelocity + angularDelta;
                shipRigidBody->linearVelocity = linearVelocity;
                _physicsSystem->commit(*shipRigidBody);

                // Apply force from primary engine thrusters
                ship.forDescendants([&](Entity& entity)
                {
                    Thruster::ConstIterator thruster = entity.component<Thruster>();
                    if (thruster && thruster->type == ThrusterType::PrimaryEngine)
                    {
                        Transform::Iterator thrusterTransform = entity.component<Transform>();
                        if (thrusterTransform)
                        {
                            const Vector3 relativePosition = shipTransform->globalRotation * thrusterTransform->localPosition;
                            const Vector3 thrustVector = shipTransform->globalRotation * directionalThrust * thruster->power * timeStep;
                            _physicsSystem->applyForce(*shipRigidBody, thrustVector, relativePosition);
                        }
                    }
                });
            }
        }
    }
}

void ShipControlSystem::debugTick(double timeStep)
{
    (void)timeStep;

    if (_debugSystem)
    {
        for (const Thruster& thruster : scene().components<Thruster>())
        {
            Entity::ConstIterator entity = thruster.entity();
            Transform::ConstIterator transform = entity->component<Transform>();
            if (transform)
            {
                const Vector3& origin = transform->globalPosition;
                Vector3 direction = transform->globalRotation * thruster.direction;

                Color color;
                switch (thruster.type)
                {
                case ThrusterType::PrimaryEngine:
                    color = Color::Red;
                    break;
                case ThrusterType::ReactionControl:
                    color = Color::Green;
                    break;
                }

                _debugSystem->renderLine(color, origin, origin + direction);
            }
        }
    }
}