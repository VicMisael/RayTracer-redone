//
// Created by Misael on 21/06/2023.
//

#include <optional>
#include <glm/gtx/norm.hpp>
#include "Disk.h"

std::tuple<float, float> Disk::getUVMapping(const Point3 point) const {
    const auto N = normalize(normal);
    const auto radius = sqrtf(this->r_squared);
    Vector3 referencevec;
    if (glm::length2(N - Vector3(0, 1, 0)) < glm::epsilon<float>()) {
        referencevec = Vector3(1, 0, 0);
    } else {
        referencevec = Vector3(0, 1, 0);
    }
    const auto U = normalize(cross(referencevec, N));
    const auto V = cross(N, U);
    const float u = dot(point - center, U);
    const float v = dot(point - center, V);
    const auto r = sqrt(u * u + v * v) / radius;
    const auto theta = atan2f(v, u);
    constexpr auto PI = (float) Constants::pi;
    return {r, (theta + PI) / 2 * PI};
    // Calculate the vector from the center of the disk to the point
}

std::optional<intersectionRec> Disk::intersects(const Ray &ray) const {
    float t = dot((center - ray.origin), normal) / dot(ray.direction, normal);

    if (t <= 0.001) {
        return {};
    }

    Point3 p = ray.origin + t * ray.direction;
    const float dist2 = powf(glm::distance(center, p), 2);
    if (dist2 < r_squared) {
        const auto [u, v] = getUVMapping(p);
        return intersectionRec{t, p, normalize(normal), material.value(), u, v};
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

