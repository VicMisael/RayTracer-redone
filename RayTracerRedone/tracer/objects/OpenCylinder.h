#pragma once

#include <utility>
#include <glm/geometric.hpp>

#include "VirtualObject.h"

class OpenCylinder: public VirtualObject {
    Vector3 axis_; // cylinder axis_
    Point3 base_;
    float height_;
    float radius_;
public:
    OpenCylinder(Vector3 axis, Point3 base, float height, float radius,std::shared_ptr<Material> _material)
            : VirtualObject(std::move(_material)), axis_(normalize(axis)), base_(base), height_(height), radius_(radius) {

    }

    std::optional<intersection> intersects(const Ray &ray) const override;

    std::optional<std::shared_ptr<AABB>> bounding_box() const override;

    virtual bool hasBoundingBox() const {
        return false;
    }
};


