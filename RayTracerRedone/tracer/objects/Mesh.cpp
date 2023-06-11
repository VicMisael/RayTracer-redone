//
// Created by Misael on 30/05/2023.
//

#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../utils/utility.h"

std::optional<intersection> Mesh::intersects(const Ray &ray) const {
    float t_min = 0;
    if (!aabb->intersects(ray, t_min)) {
        return std::nullopt;
    }

    return bvh->intersects(ray);
    /*
    float tNear = std::numeric_limits<float>::max();
    bool hit = false;
    glm::vec3 hit_normal;
    float uNear, vNear;
    float uTexture, vTexture;
    for (const Face& face : faces) {
        glm::vec3 v0 = vertices[face.v1].position;
        glm::vec3 v1 = vertices[face.v2].position;
        glm::vec3 v2 = vertices[face.v3].position;
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 h = glm::cross(ray.direction, edge2);
        float a = glm::dot(edge1, h);

        if (a < 0) {
            continue;
        }

        float f = 1.0f / a;
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

        if (t > 0.0001 && t < tNear) {
            tNear = t;
            hit = true;
            uNear = u;
            vNear = v;

            // Interpolate normal
            hit_normal = (1 - u - v) * vertices[face.v1].normal +
                u * vertices[face.v2].normal +
                v * vertices[face.v3].normal;

            // Interpolate texture coordinates
            uTexture = (1 - u - v) * vertices[face.v1].tex_coord.x +
                u * vertices[face.v2].tex_coord.x +
                v * vertices[face.v3].tex_coord.x;
            vTexture = (1 - u - v) * vertices[face.v1].tex_coord.y +
                u * vertices[face.v2].tex_coord.y +
                v * vertices[face.v3].tex_coord.y;
        }
    }

    if (hit) {
        intersection result{
                tNear,
                ray.origin + tNear * ray.direction,
                normalize(hit_normal),
                material.value(),
                uTexture,
                vTexture
        };
        return result;
    }
    else {
        return std::nullopt;
    }
    */
}

std::optional<std::shared_ptr<AABB>> Mesh::bounding_box() const {
    return aabb;
}

Mesh::Mesh(const std::string filename, const std::shared_ptr<Material> &material) :
        VirtualObject(material) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename,
                                             aiProcess_FlipUVs | aiProcess_PreTransformVertices |
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_Triangulate);

    // Error checking

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }


    //processNode(scene->mRootNode, scene);
    processScene(scene);
    calculateBoundingBox();
    GenerateBvh();
}

void Mesh::transform(Matrix4x4 m) {
    for (auto &vertex: vertices) {
        vertex.position = Vector3(m * Vector4(vertex.position, 1.0f));
        vertex.normal = normalize(Vector3(m * Vector4(vertex.normal, 0.0f)));
    }
    calculateBoundingBox();
    GenerateBvh();
}

void Mesh::calculateBoundingBox() {
    if (vertices.empty()) {
        std::cerr << "empty mesh" << std::endl;
        return;
    }

    glm::vec3 minPoint = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    glm::vec3 maxPoint = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);

    for (const auto &vertex: vertices) {
        glm::vec3 pos = vertex.position;

        minPoint = glm::min(minPoint, pos);
        maxPoint = glm::max(maxPoint, pos);
    }

    aabb = std::make_shared<AABB>(minPoint, maxPoint);
}


//void Mesh::processNode(aiNode *node, const aiScene *scene) {
//
//    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
//        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//        processMesh(mesh);
//    }
//
//    for (unsigned int i = 0; i < node->mNumChildren; i++) {
//        processNode(node->mChildren[i], scene);
//    }
//}

void Mesh::processMesh(aiMesh *mesh) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Process vertex positions
        vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};

        // Process texture coordinates if available
        if (mesh->mTextureCoords[0]) {
            vertex.tex_coord = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        } else {
            vertex.tex_coord = {0.0f, 0.0f};
        }

        // Process normals if available
        if (mesh->HasNormals()) {
            vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        } else {
            vertex.normal = {0.0f, 0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    if (!mesh->HasNormals()) {
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            glm::vec3 v1 = vertices[face.mIndices[0]].position;
            glm::vec3 v2 = vertices[face.mIndices[1]].position;
            glm::vec3 v3 = vertices[face.mIndices[2]].position;

            glm::vec3 edge1 = v2 - v1;
            glm::vec3 edge2 = v3 - v1;
            glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                vertices[face.mIndices[j]].normal = normal;
            }
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            faces.push_back({(int) face.mIndices[0], (int) face.mIndices[1], (int) face.mIndices[2]});
        }
    }
}

void Mesh::processScene(const aiScene *pScene) {
    for (unsigned int i = 0; i < pScene->mNumMeshes; i++) {
        aiMesh *mesh = pScene->mMeshes[i];
        processMesh(mesh);
    }
}

void Mesh::GenerateBvh() {

    std::vector<std::shared_ptr<VirtualObject>> triangleList;
    for (auto &item: faces) {
        auto triangle = std::make_shared<Triangle>(item, vertices, material.value());
        triangleList.push_back(triangle);
    }
    bvh = std::make_unique<BVH>(triangleList);
}


std::optional<intersection> Mesh::Triangle::intersects(const Ray &ray) const {
    float tNear = std::numeric_limits<float>::max();
    bool hit = false;
    glm::vec3 hit_normal;
    float uTexture, vTexture;
    glm::vec3 v0 = vertices[face.v1].position;
    glm::vec3 v1 = vertices[face.v2].position;
    glm::vec3 v2 = vertices[face.v3].position;
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 h = glm::cross(ray.direction, edge2);
    float a = glm::dot(edge1, h);

    if (a < 0) {
        return {};
    }

    float f = 1.0f / a;
    glm::vec3 s = ray.origin - v0;
    float u = f * glm::dot(s, h);

    if (u < 0.0 || u > 1.0) {
        return {};
    }

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.direction, q);

    if (v < 0.0 || u + v > 1.0) {
        return {};
    }

    float t = f * glm::dot(edge2, q);

    if (t > 0.0001 && t < tNear) {
        tNear = t;
        hit = true;

        // Interpolate normal
        hit_normal = (1 - u - v) * vertices[face.v1].normal +
                     u * vertices[face.v2].normal +
                     v * vertices[face.v3].normal;

        // Interpolate texture coordinates
        uTexture = (1 - u - v) * vertices[face.v1].tex_coord.x +
                   u * vertices[face.v2].tex_coord.x +
                   v * vertices[face.v3].tex_coord.x;
        vTexture = (1 - u - v) * vertices[face.v1].tex_coord.y +
                   u * vertices[face.v2].tex_coord.y +
                   v * vertices[face.v3].tex_coord.y;
    }

    if (hit) {
        return intersection{
                tNear,
                ray.origin + tNear * ray.direction,
                normalize(hit_normal),
                material.value(),
                uTexture,
                vTexture
        };

    } else {
        return std::nullopt;
    }
}


std::optional<std::shared_ptr<AABB>> Mesh::Triangle::bounding_box() const {
    glm::vec3 minPoint = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    glm::vec3 maxPoint = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);

    for (const auto &vertex: {vertices[face.v1], vertices[face.v2], vertices[face.v3]}) {
        glm::vec3 pos = vertex.position;
        minPoint = glm::min(minPoint, pos);
        maxPoint = glm::max(maxPoint, pos);
    }
    return std::make_shared<AABB>(minPoint, maxPoint);
}
