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

    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray) const override;


    virtual bool hasBoundingBox() const override{
        return false;
    }

    void transform(Matrix4x4 m) override;

    float getArea() const override;

    Point3 pointAtSurface(const Point3 &origin) const override;
};


