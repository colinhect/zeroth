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

            // Adapt planetoids
        }
    }
}

void PlanetoidSystem::onComponentAdded(Planetoid::Iterator planetoid)
{
    Entity::Iterator entity = planetoid->entity();

    Transform::Iterator transform = entity->component<Transform>();
    if (transform)
    {
        throw InvalidOperation("Planetoid cannot be created with a transform; they can only be centered at the origin");
    }
    transform = entity->addComponent<Transform>();
    transform->mobility = Mobility::Static;

    BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
    if (!boundingBox)
    {
        boundingBox = entity->addComponent<BoundingBox>();
        boundingBox->adaptive = true;
    }

    double radius = planetoid->meanRadius;

    createRootPatch(planetoid, Vector3::UnitZ, Vector3::UnitX);
    createRootPatch(planetoid, -Vector3::UnitZ, -Vector3::UnitX);
    createRootPatch(planetoid, Vector3::UnitX, Vector3::UnitY);
    createRootPatch(planetoid, -Vector3::UnitX, -Vector3::UnitY);
    createRootPatch(planetoid, Vector3::UnitY, -Vector3::UnitX);
    createRootPatch(planetoid, -Vector3::UnitY, Vector3::UnitX);

    if (_boundingBoxSystem)
    {
        _boundingBoxSystem->update(*boundingBox);
    }
}

Entity::Iterator PlanetoidSystem::createRootPatch(Planetoid::Iterator planetoid, const Vector3& up, const Vector3& right)
{
    Entity::Iterator patchEntity = scene().createEntity();
    patchEntity->setTransient(true);

    Transform::Iterator transform = patchEntity->addComponent<Transform>();
    transform->mobility = Mobility::Dynamic;
    transform->localPosition = up * planetoid->meanRadius;

    BoundingBox::Iterator boundingBox = patchEntity->addComponent<BoundingBox>();

    PlanetoidPatch::Iterator patch = patchEntity->addComponent<PlanetoidPatch>();
    
    Mesh::Handle mesh = buildPatchMesh(planetoid, patch, transform->localPosition, up, right);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, planetoid->patchMaterial);

    patchEntity->activate();

    planetoid->entity()->addChild(*patchEntity);

    return patchEntity;
}

Mesh::Handle PlanetoidSystem::buildPatchMesh(Planetoid::Iterator planetoid, PlanetoidPatch::Iterator patch, const Vector3& relativePosition, const Vector3& up, const Vector3& right)
{
    const Vector3 front = up.cross(right);
    const unsigned patchResolution = planetoid->patchResolution;
    const double patchHalfSize = patch->halfSize;
    const double faceSize = (patchHalfSize * 2) / patchResolution;
    const double planetoidMeanRadius = planetoid->meanRadius;

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution + 1; ++y)
    {
        Vector3 position = -(right + front) * patchHalfSize;
        position += front * y * faceSize;
        for (unsigned x = 0; x < patchResolution + 1; ++x)
        {
            Vector3 morphedPosition = cubeToSphere(position);
            //morphedPosition *= planetoidMeanRadius;
            //morphedPosition -= relativePosition;
            
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, morphedPosition.normalized());

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

Vector3 PlanetoidSystem::cubeToSphere(const Vector3& point)
{
    const double x2 = point.x * point.x;
    const double y2 = point.y * point.y;
    const double z2 = point.z * point.z;

    Vector3 result = point;
    result.x *= std::sqrt(1.0 - y2 / 2.0 - z2 / 2.0 + (y2 * z2) / 3.0);
    result.y *= std::sqrt(1.0 - z2 / 2.0 - x2 / 2.0 + (z2 * x2) / 3.0);
    result.z *= std::sqrt(1.0 - x2 / 2.0 - y2 / 2.0 + (x2 * y2) / 3.0);

    return result;
}
