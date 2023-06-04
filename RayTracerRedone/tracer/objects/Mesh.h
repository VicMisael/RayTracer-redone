//
// Created by Misael on 30/05/2023.
//

#pragma once
#include "VirtualObject.h"
#include <string>
#include <vector>


struct Vertex {
    Vector3 position;
    Vector2 tex_coord;
    Vector3 normal;
};

struct Face {
    int v1, v2, v3;  // Indices for vertices
};


class Mesh : public VirtualObject {
public:
    explicit Mesh(const std::string filename,const std::shared_ptr<Material> &material);

    std::optional<intersection> intersects(const Ray &ray) const override;

    std::optional<std::shared_ptr<AABB>> bounding_box() const override;

    bool hasBoundingBox() const override;

    void transform(Matrix4x4 m) override;


private:
    std::shared_ptr<AABB> aabb;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    void calculateBoundingBox();
};



