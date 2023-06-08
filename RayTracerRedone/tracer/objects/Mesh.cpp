//
// Created by Misael on 30/05/2023.
//

#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::optional<intersection> Mesh::intersects(const Ray &ray) const {
    if (!aabb->intersects(ray)) {
        return std::nullopt;
    }

    float tNear = std::numeric_limits<float>::max();
    bool hit = false;
    glm::vec3 hit_normal;
    float uNear, vNear;

    for (const Face &face : faces) {
        glm::vec3 v0 = vertices[face.v1].position;
        glm::vec3 v1 = vertices[face.v2].position;
        glm::vec3 v2 = vertices[face.v3].position;

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 h = glm::cross(ray.direction, edge2);
        float a = glm::dot(edge1, h);

        if (a >= 0) {
            continue;
        }

        float f = 1.0 / a;
        glm::vec3 s = ray.origin - v0;
        float u = f * glm::dot(s, h);

        if (u < 0.0 || u > 1.0) {
            continue;
        }

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(ray.direction, q);

        if (v < 0.0 || u + v > 1.0) {
            continue;
        }

        float t = f * glm::dot(edge2, q);

        if (t > 0.00001 && t < tNear) {
            tNear = t;
            hit = true;
            uNear = u;
            vNear = v;

            // Interpolate normal
            hit_normal = (1 - u - v) * vertices[face.v1].normal +
                         u * vertices[face.v2].normal +
                         v * vertices[face.v3].normal;
        }
    }

    if (hit) {
        intersection result {
                tNear,
                ray.origin + tNear * ray.direction,
                hit_normal,
                material.value(),
                uNear,
                vNear
        };
        return result;
    } else {
        return std::nullopt;
    }
}

std::optional<std::shared_ptr<AABB>> Mesh::bounding_box() const {
    return aabb;
}

bool Mesh::hasBoundingBox() const {
    return false;
}

Mesh::Mesh(const std::string filename,const std::shared_ptr<Material> &material) :
VirtualObject(material) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Error checking
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // Process all the model's meshes
    for(unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        for(unsigned int j = 0; j < mesh->mNumVertices; j++)
        {
            Vertex vertex;
            Vector3 vector;

            // Position
            vector.x = mesh->mVertices[j].x;
            vector.y = mesh->mVertices[j].y;
            vector.z = mesh->mVertices[j].z;
            vertex.position = vector;

            // Texture Coordinates
            if(mesh->mTextureCoords[0])
            {
                Vector2 vec;
                vec.x = mesh->mTextureCoords[0][j].x;
                vec.y = mesh->mTextureCoords[0][j].y;
                vertex.tex_coord = vec;
            }

            // Normal
            if(mesh->mNormals)
            {
                vector.x = mesh->mNormals[j].x;
                vector.y = mesh->mNormals[j].y;
                vector.z = mesh->mNormals[j].z;
                vertex.normal = vector;
            }

            vertices.push_back(vertex);
        }

        // Process indices
        for(unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            aiFace face = mesh->mFaces[j];
            Face myFace;
            myFace.v1 = face.mIndices[0];
            myFace.v2 = face.mIndices[1];
            myFace.v3 = face.mIndices[2];

            faces.push_back(myFace);
        }
    }

    calculateBoundingBox();
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
