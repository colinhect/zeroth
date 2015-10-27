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
        createRootPatch(planetoid, Vector3::UnitX, Vector3::UnitY);
        createRootPatch(planetoid, -Vector3::UnitX, -Vector3::UnitY);
        createRootPatch(planetoid, Vector3::UnitY, -Vector3::UnitX);
        createRootPatch(planetoid, -Vector3::UnitY, Vector3::UnitX);
        createRootPatch(planetoid, Vector3::UnitZ, Vector3::UnitX);
        createRootPatch(planetoid, -Vector3::UnitZ, -Vector3::UnitX);
    }
}

Entity::Iterator PlanetoidSystem::createRootPatch(Planetoid::Iterator planetoid, const Vector3& direction, const Vector3& tangent)
{
    const Vector3 bitangent = direction.cross(tangent);

    Entity::Iterator entity = scene().createEntity();
    entity->setTransient(true);

    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->dynamic = false;
    transform->localPosition = direction * planetoid->meanRadius;

    entity->addComponent<BoundingBox>();

    PlanetoidPatch::Iterator planetoidPatch = entity->addComponent<PlanetoidPatch>();
    planetoidPatch->planetoid = planetoid;
    planetoidPatch->size = planetoid->meanRadius * 2;

    double subdivideSize = planetoidPatch->size / static_cast<double>(patchResolution);
    double halfSize = planetoidPatch->size * 0.5;

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution; ++y)
    {
        for (unsigned x = 0; x < patchResolution; ++x)
        {
            Vector3 position;
            position += tangent * x * subdivideSize;
            position += bitangent * y * subdivideSize;

            position -= (Vector3::One - direction) * halfSize;
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, direction);
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

    planetoid->entity()->addChild(*entity);

    return entity;
}
