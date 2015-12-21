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
    _assetCache(engine.assetCache()),
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

            // Adapt planets
        }
    }
}

void PlanetSystem::onComponentAdded(Planet::Iterator planet)
{
    if (_planet)
    {
        throw InvalidOperation("Only one planet can exist in a scene");
    }
    else
    {
        _planet = planet;

        Entity::Iterator entity = planet->entity();

        // Add the transform component
        Transform::Iterator transform = entity->component<Transform>();
        if (!transform)
        {
            transform = entity->addComponent<Transform>();
        }
        transform->mobility = Mobility::Static;
        transform->localPosition = Vector3::Zero;
        transform->localScale = Vector3::One;
        transform->localRotation = Quaternion::Identity;

        // Add the bounding box component
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (!boundingBox)
        {
            boundingBox = entity->addComponent<BoundingBox>();
            boundingBox->adaptive = true;
        }

        // Create the root patches
        Entity::Iterator positiveX = createRootPatch(planet, CubeSide::PositiveX);
        createRootPatch(planet, CubeSide::NegativeX);
        createRootPatch(planet, CubeSide::PositiveY);
        createRootPatch(planet, CubeSide::NegativeY);
        createRootPatch(planet, CubeSide::PositiveZ);
        createRootPatch(planet, CubeSide::NegativeZ);

        split(positiveX->component<PlanetPatch>());

        // Update the bounding box
        if (_boundingBoxSystem)
        {
            _boundingBoxSystem->update(*boundingBox);
        }
    }
}

void PlanetSystem::split(PlanetPatch::Iterator patch)
{
    const Vector3& up = cubeSideUpVector(patch->cubeSide);
    const Vector3& right = cubeSideRightVector(patch->cubeSide);
    const Vector3 front = up.cross(right);

    Entity::Iterator entity = patch->entity();

    Model::Iterator model = entity->component<Model>();
    if (model)
    {
        model->visible = false;
    }

    double quarterSize = patch->halfSize * 0.5;
    for (int y = -1; y <= 1; y += 2)
    {
        for (int x = -1; x <= 1; x += 2)
        {
            createPatch(entity, patch->cubeSide, right * quarterSize * x + front * quarterSize * y);
        }
    }
}

Entity::Iterator PlanetSystem::createPatch(Entity::Iterator parent, CubeSide cubeSide, const Vector3& relativePosition)
{
    const Vector3& up = cubeSideUpVector(cubeSide);
    const Vector3& right = cubeSideRightVector(cubeSide);

    Planet::Iterator planet = parent->component<Planet>();
    PlanetPatch::Iterator parentPatch = parent->component<PlanetPatch>();

    Entity::Iterator patchEntity = scene().createEntity();
    patchEntity->setTransient(true);
    
    Transform::Iterator transform = patchEntity->addComponent<Transform>();
    transform->mobility = Mobility::Dynamic;
    transform->localPosition = relativePosition;

    BoundingBox::Iterator boundingBox = patchEntity->addComponent<BoundingBox>();

    PlanetPatch::Iterator patch = patchEntity->addComponent<PlanetPatch>();
    patch->cubeSide = cubeSide;

    if (planet)
    {
        patch->halfSize = planet->meanRadius;
    }
    else
    {
        patch->halfSize = parentPatch->halfSize * 0.5;
    }

    Mesh::Handle mesh = buildPatchMesh(_planet, patch, relativePosition);

    Model::Iterator model = patchEntity->addComponent<Model>();
    model->addSurface(mesh, _planet->patchMaterial);

    Mesh::Handle cubeMesh = _assetCache.getHandle<Mesh>("Test/Cube.Main.mesh");
    model->addSurface(cubeMesh, _planet->patchMaterial);

    patchEntity->activate();
    parent->addChild(*patchEntity);

    return patchEntity;
}

Entity::Iterator PlanetSystem::createRootPatch(Planet::Iterator planet, CubeSide cubeSide)
{
    return createPatch(planet->entity(), cubeSide, cubeSideUpVector(cubeSide) * planet->meanRadius);
}

Mesh::Handle PlanetSystem::buildPatchMesh(Planet::Iterator planet, PlanetPatch::Iterator patch, const Vector3& relativePosition)
{
    const Vector3& up = cubeSideUpVector(patch->cubeSide);
    const Vector3& right = cubeSideRightVector(patch->cubeSide);

    const Vector3 front = up.cross(right);
    const unsigned patchResolution = planet->patchResolution;
    const double patchHalfSize = patch->halfSize;
    const double faceSize = (patchHalfSize * 2) / patchResolution;
    const double planetMeanRadius = planet->meanRadius;

    Mesh::Handle mesh(new Mesh());
    mesh->setPrimitiveType(PrimitiveType::Lines);

    MeshWriter meshWriter(*mesh);
    for (unsigned y = 0; y < patchResolution + 1; ++y)
    {
        Vector3 position = -(right + front) * patchHalfSize;
        position += front * y * faceSize;
        for (unsigned x = 0; x < patchResolution + 1; ++x)
        {
            //const Vector3 morphedPosition = morphPointToSphere(position, relativePosition, planetMeanRadius);
            //const Vector3 morphedNormal = (morphedPosition + relativePosition).normalized();

            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, position);
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, (position + relativePosition).normalized());

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
