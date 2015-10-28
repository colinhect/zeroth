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
        createPatch(planetoid, PlanetoidPatch::Iterator(), Vector3::UnitZ * planetoid->meanRadius, 100, Vector3::UnitZ, Vector3::UnitX);
        createPatch(planetoid, PlanetoidPatch::Iterator(), -Vector3::UnitZ * planetoid->meanRadius, 100, -Vector3::UnitZ, -Vector3::UnitX);
        createPatch(planetoid, PlanetoidPatch::Iterator(), Vector3::UnitX * planetoid->meanRadius, 100, Vector3::UnitX, Vector3::UnitY);
        createPatch(planetoid, PlanetoidPatch::Iterator(), -Vector3::UnitX * planetoid->meanRadius, 100, -Vector3::UnitX, -Vector3::UnitY);
        createPatch(planetoid, PlanetoidPatch::Iterator(), Vector3::UnitY * planetoid->meanRadius, 100, Vector3::UnitY, -Vector3::UnitX);
        createPatch(planetoid, PlanetoidPatch::Iterator(), -Vector3::UnitY * planetoid->meanRadius, 100, -Vector3::UnitY, Vector3::UnitX);
    }
}

Entity::Iterator PlanetoidSystem::createPatch(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator parentPatch, const Vector3& localPosition, double size, const Vector3& up, const Vector3& right)
{
    Entity::Iterator patchEntity = scene().createEntity();
    patchEntity->setTransient(true);

    Transform::Iterator transform = patchEntity->addComponent<Transform>();
    transform->dynamic = false;
    transform->localPosition = localPosition;

    BoundingBox::Iterator boundingBox = patchEntity->addComponent<BoundingBox>();

    PlanetoidPatch::Iterator patch = patchEntity->addComponent<PlanetoidPatch>();
    patch->planetoid = planetoid;
    patch->size = size;

    Mesh::Handle mesh = buildPatchMesh(patch, up, right);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, patchMaterial);

    patchEntity->activate();

    Entity::Iterator parentEntity = parentPatch ? parentPatch->entity() : planetoid->entity();
    parentEntity->addChild(*patchEntity);

    return patchEntity;
}

Mesh::Handle PlanetoidSystem::buildPatchMesh(PlanetoidPatch::Iterator patch, const Vector3& up, const Vector3& right)
{
    const Vector3 front = up.cross(right);
    const unsigned patchResolution = patch->planetoid->patchResolution;
    const double halfPatchSize = patch->size * 0.5;
    const double faceSize = patch->size / static_cast<double>(patchResolution);

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Triangles);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution; ++y)
    {
        Vector3 position = -(right + front) * halfPatchSize;
        position += front * y * faceSize;
        for (unsigned x = 0; x < patchResolution; ++x)
        {
            position += right * faceSize;

            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, up);
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

    return mesh;
}
