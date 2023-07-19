//
// Created by Misael on 21/06/2023.
//

#include <optional>
#include <glm/gtx/norm.hpp>
#include "Disk.h"
#include "../utils/OrthonormalBase.h"
#include "../utils/utility.h"

std::tuple<float, float> Disk::getUVMapping(const Point3 point) const {
    glm::vec3 vecToPoint = point - center;

    // Normalize the vector
    glm::vec3 vecToPointNormalized = glm::normalize(vecToPoint);

    // Calculate the angle between the normalized vector and the disk's normal
    const float angle = std::acos(glm::dot(normal, vecToPointNormalized));

    // Calculate the radius from the center of the disk to the point
    const float radius = glm::length(vecToPoint);

    // Calculate the U coordinate (angle in radians divided by 2*pi)
    const float u = angle / (2.0f * glm::pi<float>());

    // Calculate the V coordinate (normalized radius)
    const float v = radius / sqrtf(r_squared);

    return {u, v};
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
        return intersectionRec{t, p, normalize(normal), material, u, v};
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

float Disk::getArea() const {
    constexpr auto f_pi = static_cast<float>(Constants::pi);
    return 2 * f_pi * this->r_squared;
}

std::tuple<Point3, Vector3> Disk::pointAtSurface() const {
    const OrthonormalBase uvw(this->normal);
    return {this->center + utility::random(0, 1) * (uvw.u() + uvw.v()) * sqrtf(this->r_squared), normal};
}

