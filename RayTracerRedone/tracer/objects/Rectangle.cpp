//
// Created by Misael on 25/06/2023.
//

#include <optional>
#include "Rectangle.h"
#include "../utils/utility.h"

std::optional<intersectionRec> Rectangle::intersects(const Ray &ray) const {
    float t = dot((p0 - ray.origin), normal) / dot(ray.direction, normal);

    if (t <= FLT_EPSILON) {
        return {};
    }


    const float a_len_squared = glm::length2(a);                // square of the length of side a
    const float b_len_squared = glm::length2(b);                // square of the length of side b

    Point3 p = ray.point_at(t);
    Vector3 d = p - p0;

    float ddota = dot(d, a);

    if (ddota < 0.0f || ddota > a_len_squared) {
        return {};
    }

    float ddotb = dot(d, b);

    if (ddotb < 0.0f || ddotb > b_len_squared) {
        return {};
    }
    const auto aNormalized = normalize(a);
    const auto bNormalized = normalize(b);

    const float u = fabs(dot(d, aNormalized)) / length(a);
    const float v = fabs(dot(d, bNormalized)) / length(b);


    return intersectionRec{t, p, normalize(normal), material, u, v};
}

void Rectangle::transform(Matrix4x4 m) {
    VirtualObject::transform(m);
}

std::shared_ptr<AABB> Rectangle::bounding_box() const {
    constexpr float delta = 0.0001;
    const auto min = glm::min(p0, p0 + a + b - Vector3(delta));
    const auto max = glm::max(p0, p0 + a + b + Vector3(delta));
    return std::make_shared<AABB>(AABB(min, max));
}

float Rectangle::getArea() const {
    return length(a) * length(b);
}

std::tuple<Point3, Vector3> Rectangle::pointAtSurface() const {
    const auto sample_point = utility::random_unit_square();
    return {(p0 + sample_point.x * a + sample_point.y * b), normal};
}

float Rectangle::getPdf() const {
    return 1 / getArea();
}
