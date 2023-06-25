//
// Created by Misael on 25/06/2023.
//

#include <optional>
#include "Rectangle.h"

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


    return intersectionRec{t, p, normalize(normal), material.value(), ddota / length(a), 1 - ddotb / length(b)};
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
