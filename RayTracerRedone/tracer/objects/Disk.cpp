//
// Created by Misael on 21/06/2023.
//

#include <optional>
#include "Disk.h"

std::tuple<float,float> getUVMapping(const glm::vec3& point, const glm::vec3& center, const glm::vec3& normal, float radiusSquared)
{
    // Calculate the vector from the center of the disk to the point
    glm::vec3 vecToPoint = point - center;

    // Normalize the vector
    glm::vec3 vecToPointNormalized = glm::normalize(vecToPoint);

    // Calculate the angle between the normalized vector and the disk's normal
    float angle = std::acos(glm::dot(normal, vecToPointNormalized));

    // Calculate the radius from the center of the disk to the point
    float radius = glm::length(vecToPoint);

    // Calculate the U coordinate (angle in radians divided by 2*pi)
    float u = angle / (2.0f * glm::pi<float>());

    // Calculate the V coordinate (normalized radius)
    float v = radius/sqrt(radiusSquared);

    return {u, v};
}

std::optional<intersectionRec> Disk::intersects(const Ray &ray) const {
    float t = dot((center - ray.origin), normal) / dot(ray.direction, normal);

    if (t <= 0.001) {
        return {};
    }

    Point3 p = ray.origin + t * ray.direction;
    const float dist2 = powf(glm::distance(center, p), 2);
    if (dist2 < r_squared) {
       const auto [u,v] =getUVMapping(p,center, normalize(normal),r_squared);
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

