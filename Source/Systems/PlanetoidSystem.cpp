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

    Entity::Iterator parentEntity = parentPatch ? parentPatch->entity() : planetoid->entity();
    Transform::Iterator parentTransform = parentEntity->component<Transform>();
    Vector3 relativePosition = parentTransform->globalPosition + localPosition;

    Mesh::Handle mesh = buildPatchMesh(patch, relativePosition, up, right);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, planetoid->patchMaterial);

    patchEntity->activate();

    parentEntity->addChild(*patchEntity);

    return patchEntity;
}

Mesh::Handle PlanetoidSystem::buildPatchMesh(PlanetoidPatch::Iterator patch, const Vector3& relativePosition, const Vector3& up, const Vector3& right)
{
    const Vector3 front = up.cross(right);
    const unsigned patchResolution = patch->planetoid->patchResolution;
    const double halfPatchSize = patch->size * 0.5;
    const double faceSize = patch->size / static_cast<double>(patchResolution);
    const double planetoidMeanRadius = patch->planetoid->meanRadius;

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution + 1; ++y)
    {
        Vector3 position = -(right + front) * halfPatchSize;
        position += front * y * faceSize;
        for (unsigned x = 0; x < patchResolution + 1; ++x)
        {
            Vector3 morphedPosition = cubeToSphere(position, relativePosition, planetoidMeanRadius);
            const Vector3 normal = (morphedPosition + relativePosition).normalized();

            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, morphedPosition);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, normal);

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

Vector3 PlanetoidSystem::cubeToSphere(const Vector3& localPosition, const Vector3& relativePosition, double radius)
{
    Vector3 morphedPosition = localPosition;
    morphedPosition += relativePosition;
    morphedPosition /= radius;

    const double x2 = morphedPosition.x * morphedPosition.x;
    const double y2 = morphedPosition.y * morphedPosition.y;
    const double z2 = morphedPosition.z * morphedPosition.z;
    morphedPosition.x *= std::sqrt(1.0 - y2 / 2.0 - z2 / 2.0 + (y2 * z2) / 3.0);
    morphedPosition.y *= std::sqrt(1.0 - z2 / 2.0 - x2 / 2.0 + (z2 * x2) / 3.0);
    morphedPosition.z *= std::sqrt(1.0 - x2 / 2.0 - y2 / 2.0 + (x2 * y2) / 3.0);

    morphedPosition *= radius;
    morphedPosition -= relativePosition;

    return morphedPosition;
}
