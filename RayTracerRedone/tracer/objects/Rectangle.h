//
// Created by Misael on 25/06/2023.
//

#pragma once

#include <glm/gtx/norm.hpp>
#include "VirtualObject.h"

class Rectangle : public VirtualObject {
    Point3 p0 = Point3(-1.0f, 0.0f, -1.0f);  // corner vertex
    Vector3 a = Vector3(0.0f, 0.0f, 2.0f);   // side
    Vector3 b = Vector3(2.0f, 0.0f, 0.0f);   // side

    Vector3 normal = Vector3(0.0f, 1.0f, 0.0f);
    float area ;
public:
    Rectangle(const Point3 &_p0, const Vector3 &_a, const Vector3 &_b, std::shared_ptr<Material> _material)
            : VirtualObject(_material), p0(_p0), a(_a), b(_b),
              area(length(a) * length(b)) {
        normal = cross(a, b);
        normal = normalize(normal);
    }

    Rectangle(const Point3 &_p0, const Vector3 &_normal, const float side_length, std::shared_ptr<Material> _material)
            : VirtualObject(_material), p0(_p0) {
        Vector3 refDir;
        auto axisNormalized = normalize(_normal);
        if (glm::length2(axisNormalized - Vector3(0, 1, 0)) < glm::epsilon<float>()) {
            refDir = Vector3(1, 0, 0);
        } else {
            refDir = Vector3(0, 1, 0);
        }

        auto t = cross(refDir,axisNormalized);
        auto bvec = cross(axisNormalized,t);
        a = t * side_length;
        b = bvec * side_length;
        normal = axisNormalized;
    }

    Rectangle(const Point3 &_p0, const Vector3 &_a, const Vector3 &_b, const Vector3 &_normal,std::shared_ptr<Material> _material)
            : VirtualObject(_material), p0(_p0), a(_a), b(_b),
              area(length(a) * length(b)), normal(_normal) {
        normal = normalize(normal);
    }

    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray) const override;

    void transform(Matrix4x4 m) override;

    std::shared_ptr<AABB> bounding_box() const override;

    float getArea() const override;;
};


