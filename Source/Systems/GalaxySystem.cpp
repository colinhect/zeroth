///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "GalaxySystem.h"

using namespace zeroth;

GalaxySystem::GalaxySystem(Scene& scene) :
    System(scene),
    _cameraSystem(scene.system<CameraSystem>())
{
}

void GalaxySystem::initialize()
{
}

void GalaxySystem::tick(double timeStep)
{
    (void)timeStep;

    if (_cameraSystem)
    {
        // If there is an active camera
        Camera::Iterator activeCamera = _cameraSystem->activeCamera();
        if (activeCamera)
        {
            Vector3 cameraPosition = activeCamera->position;

            // For each galaxy
            for (Galaxy& galaxy : scene().components<Galaxy>())
            {
                // Adapt each root galaxy node to the camera position
                Entity::Iterator galaxyEntity = galaxy.entity();
                for (Entity& child : galaxyEntity->children())
                {
                    Entity::Iterator rootGalaxyNode = child.iterator();
                    adaptGalaxyNode(cameraPosition, rootGalaxyNode);
                }
            }
        }
    }
}

void GalaxySystem::onComponentAdded(Galaxy::Iterator galaxy)
{
    generateGalaxy(galaxy);
}

void GalaxySystem::generateGalaxy(Galaxy::Iterator galaxy)
{
    Entity::Iterator entity = galaxy->entity();

    // Create the random number generator for this galaxy
    Random random;
    if (galaxy->seed != 0)
    {
        random = Random(galaxy->seed);
    }
    
    // Generate the numerical properties about the galaxy
    galaxy->diameter = random.next(spiralDiameterRange[0], spiralDiameterRange[1]);
    HECT_DEBUG(format("Diameter: %f ly", galaxy->diameter));
    galaxy->thickness = random.next(spiralThicknessRange[0], spiralThicknessRange[1]);
    HECT_DEBUG(format("Thickness: %f ly", galaxy->thickness));
    galaxy->eccentricity = random.next(0.0, 1.0);
    HECT_DEBUG(format("Eccentricity: %f", galaxy->eccentricity));
    galaxy->armThickness = random.next(0.0, 1.0);
    HECT_DEBUG(format("Arm Thickness: %f", galaxy->armThickness));

    // Compute minimum
    double horizontalRadius = galaxy->diameter / 2.0;
    double verticalRadius = galaxy->thickness / 2.0;
    const Vector3 minimum(-horizontalRadius, -horizontalRadius, -verticalRadius);

    // Compute the ratio of horizontal to vertical nodes
    double ratio = horizontalRadius / verticalRadius;
    int rootNodeCount = static_cast<int>(ratio);

    // The size of each root node
    Vector3 size(horizontalRadius * 2.0 / rootNodeCount);
    size.z = verticalRadius * 2.0;
    Vector3 halfSize = size / 2.0;

    // Create the root nodes of the galaxy
    for (int x = 0; x < rootNodeCount; ++x)
    {
        for (int y = 0; y < rootNodeCount; ++y)
        {
            Vector3 localPosition = minimum + size * Vector3(x, y, 0) + halfSize;
            Entity::Iterator rootGalaxyNode = createGalaxyNode(galaxy, size, localPosition, Vector3::Zero);
            entity->addChild(*rootGalaxyNode);
        }
    }

    // Add the bounding box for the whole galaxy
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();

    // Add the model for the topology and particle layer meshes
    Model::Iterator model = entity->addComponent<Model>();

    createTopologyMesh(galaxy);
}

void GalaxySystem::createTopologyMesh(Galaxy::Iterator galaxy)
{
    // Create mesh
    Mesh::Handle topologyMesh(new Mesh("Topology"));
    topologyMesh->setPrimitiveType(PrimitiveType::Triangles);

    // Write the vertex/index data
    VertexAttributeSemantic position = VertexAttributeSemantic::Position;
    VertexAttributeSemantic textureCoords = VertexAttributeSemantic::TextureCoords0;
    MeshWriter meshWriter(*topologyMesh);
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(-0.5, -0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(0.0, 0.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(0.5, -0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(1.0, 0.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(0.5, 0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(1.0, 1.0));
    meshWriter.addVertex();
    meshWriter.writeAttributeData(position, Vector2(-0.5, 0.5) * galaxy->diameter);
    meshWriter.writeAttributeData(textureCoords, Vector2(0.0, 1.0));
    meshWriter.addIndex(0);
    meshWriter.addIndex(1);
    meshWriter.addIndex(2);
    meshWriter.addIndex(2);
    meshWriter.addIndex(3);
    meshWriter.addIndex(0);

    // Temp
    AssetCache& assetCache = Engine::instance().assetCache();
    Texture2::Handle tempTexture = assetCache.getHandle<Texture2>("Galaxy/Materials/Textures/ComplexDust.texture2");

    // Create the material
    Material::Handle topologyMaterial(new Material("Topology"));
    topologyMaterial->setShader(topologyShader);
    topologyMaterial->setUniformValue("texture", tempTexture);
    topologyMaterial->setCullMode(CullMode::None);

    // Add the mesh to the galaxy's model
    Model::Iterator model = galaxy->entity()->component<Model>();
    model->addSurface(topologyMesh, topologyMaterial);
}

Entity::Iterator GalaxySystem::createGalaxyNode(Galaxy::Iterator galaxy, const Vector3& size, const Vector3& localPosition, const Vector3& parentGlobalPosition)
{
    // Create the galaxy node entity
    Entity::Iterator entity = scene().createEntity();
    entity->setTransient(true);

    // Add transform component
    Transform::Iterator transform = entity->addComponent<Transform>();
    transform->localPosition = localPosition;
    transform->globalPosition = parentGlobalPosition + localPosition;

    // Add bounding box component
    BoundingBox::Iterator boundingBox = entity->addComponent<BoundingBox>();
    boundingBox->adaptive = false;
    Vector3 minimum = parentGlobalPosition + localPosition;
    Vector3 halfSize = size / 2;
    boundingBox->extents = AxisAlignedBox(minimum - size / 2, minimum + size / 2);

    // Add galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->addComponent<GalaxyNode>();
    galaxyNode->galaxy = galaxy;
    galaxyNode->radius = size.length() / 2;
    
    // Activate and return the entity
    entity->activate();
    return entity;
}

void GalaxySystem::adaptGalaxyNode(const Vector3& cameraPosition, Entity::Iterator entity)
{
    // Get the galaxy node component
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode)
    {
        // Get the transform component
        Transform::Iterator transform = entity->component<Transform>();
        if (transform)
        {
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            // Compute the distance from the camera to the node
            double distance = (cameraPosition - transform->globalPosition).length();

            // If the node is split and it is far enough away to join
            if (galaxyNode->split && distance > galaxyNode->radius * 2.0)
            {
                joinGalaxyNode(entity);
            }

            // If the node is not split and is close enough to split
            else if (!galaxyNode->split && distance < galaxyNode->radius * 1.9)
            {
                splitGalaxyNode(entity);
            }
            else
            {
                for (Entity& child : entity->children())
                {
                    adaptGalaxyNode(cameraPosition, child.iterator());
                }
            }
        }
    }
}

void GalaxySystem::joinGalaxyNode(Entity::Iterator entity)
{
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && galaxyNode->split)
    {
        entity->destroyAllChildren();
        galaxyNode->split = false;
    }
}

void GalaxySystem::splitGalaxyNode(Entity::Iterator entity)
{
    // If the node is not split and is not at the maximum level
    GalaxyNode::Iterator galaxyNode = entity->component<GalaxyNode>();
    if (galaxyNode && !galaxyNode->split && galaxyNode->radius > 600.0)
    {
        Entity::Iterator parent = entity->iterator();

        // Get the bounding box component
        BoundingBox::Iterator boundingBox = entity->component<BoundingBox>();
        if (boundingBox)
        {
            Galaxy::Iterator galaxy = galaxyNode->galaxy;

            Vector3 size = boundingBox->extents.size() / 2;
            Vector3 halfSize = size / 2;
            Vector3 parentGlobalPosition = boundingBox->extents.center();

            // Create the child nodes
            std::vector<int> values { -1, 1 };
            for (int x : values)
            {
                for (int y : values)
                {
                    for (int z : values)
                    {
                        const Vector3 localPosition = halfSize * Vector3(x, y, z);
                        Entity::Iterator child = createGalaxyNode(galaxy, size, localPosition, parentGlobalPosition);
                        parent->addChild(*child);
                    }
                }
            }

            galaxyNode->split = true;
        }
    }
}
