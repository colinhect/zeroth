///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "PlanetSystem.h"

using namespace zeroth;

PlanetSystem::PlanetSystem(Engine& engine, Scene& scene) :
    System(engine, scene),
    _boundingBoxSystem(scene.system<BoundingBoxSystem>()),
    _cameraSystem(scene.system<CameraSystem>()),
    _transformSystem(scene.system<TransformSystem>())
{
}

void PlanetSystem::initialize()
{
}

void PlanetSystem::tick(double timeStep)
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

void PlanetSystem::onComponentAdded(Planet::Iterator planetoid)
{
    Entity::Iterator entity = planetoid->entity();

    if (entity->hasComponent<Transform>())
    {
        throw InvalidOperation("Planet cannot be created with a transform; they can only be centered at the origin");
    }

    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->mobility = Mobility::Static;

    BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
    if (!boundingBox)
    {
        boundingBox = entity->addComponent<BoundingBox>();
        boundingBox->adaptive = true;
    }

    createRootPatch(planetoid, CubeSide::PositiveX);
    createRootPatch(planetoid, CubeSide::NegativeX);
    createRootPatch(planetoid, CubeSide::PositiveY);
    createRootPatch(planetoid, CubeSide::NegativeY);
    createRootPatch(planetoid, CubeSide::PositiveZ);
    createRootPatch(planetoid, CubeSide::NegativeZ);

    if (_boundingBoxSystem)
    {
        _boundingBoxSystem->update(*boundingBox);
    }
}

Entity::Iterator PlanetSystem::createRootPatch(Planet::Iterator planetoid, CubeSide cubeSide)
{
    const Vector3& up = cubeSideUpVector(cubeSide);
    const Vector3& right = cubeSideRightVector(cubeSide);

    Entity::Iterator patchEntity = scene().createEntity();
    patchEntity->setTransient(true);

    Vector3 patchPosition = up * planetoid->meanRadius;

    Transform::Iterator transform = patchEntity->addComponent<Transform>();
    transform->mobility = Mobility::Dynamic;
    transform->localPosition = patchPosition;

    BoundingBox::Iterator boundingBox = patchEntity->addComponent<BoundingBox>();

    PlanetPatch::Iterator patch = patchEntity->addComponent<PlanetPatch>();
    patch->cubeSide = cubeSide;
    patch->halfSize = planetoid->meanRadius;

    Mesh::Handle mesh = buildPatchMesh(planetoid, patch, patchPosition);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, planetoid->patchMaterial);

    patchEntity->activate();

    planetoid->entity()->addChild(*patchEntity);

    return patchEntity;
}

Mesh::Handle PlanetSystem::buildPatchMesh(Planet::Iterator planetoid, PlanetPatch::Iterator patch, const Vector3& relativePosition)
{
    const Vector3& up = cubeSideUpVector(patch->cubeSide);
    const Vector3& right = cubeSideRightVector(patch->cubeSide);

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
            const Vector3 morphedPosition = morphPointToSphere(position, relativePosition, planetoidMeanRadius);
            const Vector3 morphedNormal = (morphedPosition + relativePosition).normalized();

            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, morphedPosition);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, morphedNormal);

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

Vector3 PlanetSystem::morphPointToSphere(const Vector3& point, const Vector3& relativePosition, double radius)
{
    Vector3 unitPosition = (relativePosition + point) / radius;

    Vector3 result = projectUnitCubeToSphere(unitPosition);
    result *= radius;
    result -= relativePosition;

    return result;
}

Vector3 PlanetSystem::projectUnitCubeToSphere(const Vector3& point)
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

const Vector3& PlanetSystem::cubeSideUpVector(CubeSide cubeSide)
{
    static Vector3 _vectors[6] =
    {
        Vector3::UnitX,
        -Vector3::UnitX,
        Vector3::UnitY,
        -Vector3::UnitY,
        Vector3::UnitZ,
        -Vector3::UnitZ
    };

    return _vectors[static_cast<int>(cubeSide)];
}

const Vector3& PlanetSystem::cubeSideRightVector(CubeSide cubeSide)
{
    static Vector3 _vectors[6] =
    {
        Vector3::UnitY,
        -Vector3::UnitY,
        -Vector3::UnitX,
        Vector3::UnitX,
        Vector3::UnitX,
        -Vector3::UnitX
    };

    return _vectors[static_cast<int>(cubeSide)];
}
