#pragma once

#include "VirtualObject.h"
#include "glm/geometric.hpp"

class Plane : public VirtualObject {
public:
    Point3 point;
    Vector3 normal;

    Plane(Point3 _point, Vector3 _normal, std::shared_ptr<Material> _material) : VirtualObject(_material),
                                                                                 point(_point),
                                                                                 normal(normalize(_normal)) {};

    std::optional<intersection> intersects(const Ray &ray) const override;

    bool hasBoundingBox() const override  {
        return false;
    };


};

