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
    _boundingBoxSystem(scene.system<BoundingBoxSystem>()),
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
        throw InvalidOperation("Planetoid cannot be created with a transform");
    }
    transform = entity->addComponent<Transform>();
    transform->dynamic = false;

    BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
    if (!boundingBox)
    {
        boundingBox = entity->addComponent<BoundingBox>();
        boundingBox->adaptive = true;
    }

    double radius = planetoid->meanRadius;

    PlanetoidPatch::Iterator none;
    createPatch(planetoid, none, Vector3::UnitZ * radius, radius * 2, Vector3::UnitZ, Vector3::UnitX);
    createPatch(planetoid, none, -Vector3::UnitZ * radius, radius * 2, -Vector3::UnitZ, -Vector3::UnitX);
    createPatch(planetoid, none, Vector3::UnitX * radius, radius * 2, Vector3::UnitX, Vector3::UnitY);
    createPatch(planetoid, none, -Vector3::UnitX * radius, radius * 2, -Vector3::UnitX, -Vector3::UnitY);
    createPatch(planetoid, none, Vector3::UnitY * radius, radius * 2, Vector3::UnitY, -Vector3::UnitX);
    createPatch(planetoid, none, -Vector3::UnitY * radius, radius * 2, -Vector3::UnitY, Vector3::UnitX);

    if (_boundingBoxSystem)
    {
        _boundingBoxSystem->update(*boundingBox);
    }
}

Entity::Iterator PlanetoidSystem::createPatch(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator parentPatch, const Vector3& localPosition, double size, const Vector3& up, const Vector3& right)
{
    Entity::Iterator patchEntity = scene().createEntity();
    patchEntity->setTransient(true);

    Transform::Iterator transform = patchEntity->addComponent<Transform>();
    transform->dynamic = true;
    transform->localPosition = localPosition;

    BoundingBox::Iterator boundingBox = patchEntity->addComponent<BoundingBox>();

    PlanetoidPatch::Iterator patch = patchEntity->addComponent<PlanetoidPatch>();
    patch->planetoid = planetoid;
    patch->size = size;

    Mesh::Handle mesh = buildPatchMesh(patch, up, right);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, planetoid->patchMaterial);

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
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution + 1; ++y)
    {
        Vector3 position = -(right + front) * halfPatchSize;
        position += front * y * faceSize;
        for (unsigned x = 0; x < patchResolution + 1; ++x)
        {
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, up);

            position += right * faceSize;
        }
    }

    unsigned verticesPerRow = patchResolution + 1;

    for (unsigned y = 0; y < patchResolution; ++y)
    {
        for (unsigned x = 0; x < patchResolution; ++x)
        {
            meshWriter.addIndex(y * verticesPerRow + x);
            meshWriter.addIndex(y * verticesPerRow + x + 1);
            meshWriter.addIndex((y + 1) * verticesPerRow + x + 1);
            meshWriter.addIndex((y + 1) * verticesPerRow + x + 1);
            meshWriter.addIndex((y + 1) * verticesPerRow + x);
            meshWriter.addIndex(y * verticesPerRow + x);
        }
    }

    return mesh;
}
