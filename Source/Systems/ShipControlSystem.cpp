///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ShipControlSystem.h"

#include "Components/ThrusterComponent.h"

using namespace zeroth;

ShipControlSystem::ShipControlSystem(Engine& engine, Scene& scene) :
    System(engine, scene)
{
}

void ShipControlSystem::controlShip(Entity& ship, Vector3 directionalThrust, Vector3 angularThrust, Seconds timeStep)
{
    TransformComponent::Iterator shipTransform = ship.component<TransformComponent>();
    if (shipTransform)
    {
        RigidBodyComponent::Iterator shipRigidBody = ship.component<RigidBodyComponent>();
        if (shipRigidBody)
        {
            auto& physicsSystem = scene().system<PhysicsSystem>();

            if (angularThrust != Vector3::Zero)
            {
                Vector3 angularVelocity = shipRigidBody->angularVelocity;
                Vector3 linearVelocity = shipRigidBody->linearVelocity;

                // Apply friction to angular velocity
                angularVelocity = angularVelocity - angularVelocity * timeStep.value * 1.0;

                // Compute angular velocity delta based on control amount
                Vector3 angularDelta = shipTransform->globalRotation * angularThrust;
                angularDelta *= timeStep.value * 2.0;

                // Apply fiction to linear velocity
                linearVelocity = linearVelocity - linearVelocity * timeStep.value * 0.5;

                // Update the rigidy body based on new linear and angular velocities
                shipRigidBody->angularVelocity = angularVelocity + angularDelta;
                shipRigidBody->linearVelocity = linearVelocity;
                physicsSystem.commitRigidBody(*shipRigidBody);
            }

            if (directionalThrust != Vector3::Zero)
            {
                // Apply force from primary engine thrusters
                ship.forDescendants([&](Entity& entity)
                {
                    ThrusterComponent::ConstIterator thruster = entity.component<ThrusterComponent>();
                    if (thruster)
                    {
                        TransformComponent::Iterator thrusterTransform = entity.component<TransformComponent>();
                        if (thrusterTransform)
                        {
                            const Vector3 relativePosition = shipTransform->globalRotation * thrusterTransform->localPosition;
                            const Vector3 thrustVector = shipTransform->globalRotation * directionalThrust * thruster->power * timeStep.value;
                            physicsSystem.applyForceToRigidBody(*shipRigidBody, thrustVector, relativePosition);
                        }
                    }
                });
            }
        }
    }
}

void ShipControlSystem::renderDebugGeometry()
{
    for (const ThrusterComponent& thruster : scene().components<ThrusterComponent>())
    {
        Entity::ConstIterator entity = thruster.entity();
        TransformComponent::ConstIterator transform = entity->component<TransformComponent>();
        if (transform)
        {
            Vector3 origin = transform->globalPosition;
            Vector3 direction = transform->globalRotation * thruster.direction;

            if (scene().hasSystemType<DebugSystem>())
            {
                auto& debugSystem = scene().system<DebugSystem>();
                debugSystem.renderLine(Color::Red, origin, origin + direction);
            }
        }
    }
}
