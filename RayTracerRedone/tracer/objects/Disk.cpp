//
// Created by Misael on 21/06/2023.
//

#include <optional>
#include "Disk.h"

std::optional<intersectionRec> Disk::intersects(const Ray &ray) const {
    float t = dot((center - ray.origin), normal) / dot(ray.direction, normal);

    if (t <= FLT_EPSILON) {
        return {};
    }

    Point3 p = ray.origin + t * ray.direction;
    const float dist2 = powf(glm::distance(center, p), 2);
    if (dist2 < r_squared) {
        return intersectionRec{t, p, normalize(normal), material.value(), 0, 0};
    } else {
        return {};
    }
}

void Disk::transform(Matrix4x4 m) {
    center = Vector3(m * Vector4(center, 1));
    normal = Vector3(m * Vector4(normal, 0));
    VirtualObject::transform(m);
}

std::shared_ptr<AABB> Disk::bounding_box() const {
    return VirtualObject::bounding_box();
}

bool Disk::hasBoundingBox() const {
    return false;
}

