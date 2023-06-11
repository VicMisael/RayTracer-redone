//
// Created by Misael on 30/05/2023.
//

#pragma once

#include "VirtualObject.h"
#include "BoundingBox/BVH.h"
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    Vector3 position;
    Vector2 tex_coord;
    Vector3 normal;
};

struct Face {
    int v1, v2, v3;  // Indices for vertices
};


class Mesh : public VirtualObject {
protected:
    void calculateBoundingBox() ;
public:
    explicit Mesh(std::string filename, const std::shared_ptr<Material> &material);

    [[nodiscard]] std::optional<intersection> intersects(const Ray &ray) const override;

    [[nodiscard]] std::shared_ptr<AABB> bounding_box() const  override;


    void transform(Matrix4x4 m) override;


private:
    std::shared_ptr<AABB> aabb;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::unique_ptr<BVH> bvh;



    void processNode(aiNode *node, const aiScene *scene);

    void processMesh(aiMesh *mesh);

    void processScene(const aiScene *pScene);

    void GenerateBvh();

    class Triangle : public VirtualObject {
        std::vector<Vertex> &vertices;
        Face &face;
    public:
        Triangle(Face &face_,std::vector<Vertex> &vertices_,const std::shared_ptr<Material> meshMaterial):face(face_),vertices(vertices_),VirtualObject(meshMaterial){

        };
        [[nodiscard]] std::optional<intersection> intersects(const Ray &ray) const override;

        void transform(Matrix4x4 m) override{};

        [[nodiscard]] std::shared_ptr<AABB> bounding_box() const override  ;

    };


};



