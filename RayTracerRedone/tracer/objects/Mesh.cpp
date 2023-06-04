//
// Created by Misael on 30/05/2023.
//

#include "Mesh.h"
#include <iostream>

std::optional<intersection> Mesh::intersects(const Ray &ray) const {
    return {};
}

std::optional<std::shared_ptr<AABB>> Mesh::bounding_box() const {
    return aabb;
}

bool Mesh::hasBoundingBox() const {
    return false;
}

Mesh::Mesh(const std::string filename,const std::shared_ptr<Material> &material) :
VirtualObject(material) {
    //TODO: Usar Assimp mesmo
    calculateBoundingBox();
}

void Mesh::transform(Matrix4x4 m) {
    for(auto& vertex : vertices) {
            vertex.position=Vector3(m*Vector4(vertex.position,1.0f));
            vertex.normal= normalize(Vector3(m*Vector4(vertex.normal,0.0f)));
    }
    calculateBoundingBox();
}

void Mesh::calculateBoundingBox()
{
    if (vertices.empty())
    {
        std::cerr << "empty mesh" << std::endl;
        return;
    }

    glm::vec3 minPoint = glm::vec3(-std::numeric_limits<float>::max());
    glm::vec3 maxPoint = glm::vec3(std::numeric_limits<float>::max());

    for (const auto& vertex : vertices)
    {
        glm::vec3 pos = vertex.position;

        minPoint = glm::min(minPoint, pos);
        maxPoint = glm::max(maxPoint, pos);
    }

    aabb = std::make_shared<AABB>(minPoint, maxPoint);
}
