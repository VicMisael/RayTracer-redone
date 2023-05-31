//
// Created by Misael on 30/05/2023.
//

#include "OpenCylinder.h"

std::optional<intersection> OpenCylinder::intersects(const Ray &ray) const {

    float t_min = INFINITY;
    const Point3 &p0 = ray.origin;
    const Vector3 &d = ray.direction;
    const Vector3 pMBase = (p0 - base_);
    const Vector3 v = pMBase - (axis_ * (dot(pMBase, axis_)));
    const Vector3 w = d - (axis_ * (dot(d, axis_)));
    const float a = dot(w, w);
    const float b = dot(v, w);
    const float c = dot(v, v) - radius_ * radius_;
    const float delta = b * b - (a * c);
    if(delta<0){
        return {};
    }
    const auto intersection1 = (-1 * b + sqrtf(delta)) / a;
    const auto intersection2 = (-1 * b - sqrtf(delta)) / a;

    Point3 p0r = ray.point_at(intersection1);
    Point3 p1r = ray.point_at(intersection2);
    float hPo = dot(base_ - p0r, axis_);
    float hPo1 = dot(base_ - p1r, axis_);
    int intersecs = 0;
    if ((0 <= hPo && hPo <= height_))
    {
        intersecs++;
        t_min = std::min(intersection1, t_min);
    }
    if ((0 <= hPo1 && hPo1 <= height_))
    {
        intersecs++;
        t_min = std::min(intersection2, t_min);
    }

    if(intersecs>0){
        const auto intersectionPoint= ray.point_at(t_min);
        const auto W = intersectionPoint - base_;
        const auto unnormalizedNormal = (W-axis_*(dot(W,axis_)));

        return intersection{true,t_min,intersectionPoint, normalize(unnormalizedNormal),material.value()};
    };
    return {};

}
