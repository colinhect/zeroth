///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlanetoidSystem.h"

using namespace zeroth;

PlanetoidSystem::PlanetoidSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _cameraSystem(scene.system<CameraSystem>())
{
}

void PlanetoidSystem::initialize()
{
}

void PlanetoidSystem::tick(double timeStep)
{
    (void)timeStep;

    if (_cameraSystem)
    {
        Camera::Iterator activeCamera = _cameraSystem->activeCamera();
        if (activeCamera)
        {
            Vector3 cameraPosition = activeCamera->position;

        }
    }
}

void PlanetoidSystem::onComponentAdded(Planetoid::Iterator planetoid)
{
    Entity::Iterator entity = planetoid->entity();
    Transform::Iterator transform = entity->component<Transform>();
    if (transform)
    {
        createPatch(planetoid, planetoid->size, Vector3::Zero, Vector3::Zero);
    }
}

Entity::Iterator PlanetoidSystem::createPatch(Planetoid::Iterator planetoid, double size, const Vector3& localPosition, const Vector3& parentGlobalPosition)
{
    Entity::Iterator entity = scene().createEntity();
    entity->setTransient(true);

    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->dynamic = false;
    transform->localPosition = localPosition;
    transform->globalPosition = parentGlobalPosition + localPosition;

    entity->addComponent<BoundingBox>();

    PlanetoidPatch::Iterator planetoidPatch = entity->addComponent<PlanetoidPatch>();
    planetoidPatch->terrain = planetoid;
    planetoidPatch->size = size;

    double subdivideSize = size / static_cast<double>(patchResolution);

    double halfSize = size * 0.5;

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned x = 0; x < patchResolution; ++x)
    {
        for (unsigned y = 0; y < patchResolution; ++y)
        {
            Vector3 position(x * subdivideSize, y * subdivideSize, 0);
            position -= Vector3(1, 1, 0) * halfSize;
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, Vector3::UnitZ);
        }
    }

    for (unsigned y = 0; y < patchResolution - 1; ++y)
    {
        for (unsigned x = 0; x < patchResolution - 1; ++x)
        {
            meshWriter.addIndex(y * patchResolution + x);
            meshWriter.addIndex((y + 1) * patchResolution + x);
            meshWriter.addIndex((y + 1) * patchResolution + x + 1);

            meshWriter.addIndex((y + 1) * patchResolution + x + 1);
            meshWriter.addIndex(y * patchResolution + x + 1);
            meshWriter.addIndex(y * patchResolution + x);
        }
    }

    Model::Iterator model = entity->addComponent<Model>();
    model->addSurface(mesh, patchMaterial);

    entity->activate();
    return entity;
}
