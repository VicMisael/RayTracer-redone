//
// Created by Misael on 30/05/2023.
//

#include "OpenCylinder.h"
#include <cmath>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>


std::tuple<float,float> getUV(const Vector3& point, const Vector3& base, const Vector3& axis, float height, float radius) {
    // Normalize axis
    Vector3 axisNormalized = glm::normalize(axis);

    // Calculate the point's position relative to the base of the cylinder
    Vector3 relPoint = point - base;

    // Compute 'v' coordinate by projecting relPoint onto axisNormalized (dot product)
    float v = dot(relPoint, axisNormalized);

    // Remove the part of relPoint that lies along the cylinder's axis
    Vector3 radialVec = relPoint - v * axisNormalized;
    Vector3 refDir;
    // Compute 'u' coordinate as the angle between radialVec and a reference direction (e.g., (1,0,0))
    if(glm::length2(axisNormalized - Vector3(0,1,0)) < glm::epsilon<float>())
    {
        refDir = Vector3(1, 0, 0);
    }
    else
    {
        refDir = Vector3(0, 1, 0);
    }
    float dotProduct = dot(radialVec, refDir);
    float crossProductLength = glm::length(glm::cross(radialVec, refDir));
    float u = glm::atan(crossProductLength, dotProduct) / (2 * glm::pi<float>());

    // Normalize 'v' to [0,1] by dividing by the height of the cylinder
    v /= height;
    return { u,v };
}
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

    if(intersecs>0 && std::fabs(t_min)>glm::epsilon<float>()){
        const auto intersectionPoint= ray.point_at(t_min);
        const auto W = intersectionPoint - base_;
        const auto unnormalizedNormal = (W-axis_*(dot(W,axis_)));
        const auto  [ u, v ] = getUV(intersectionPoint,base_,axis_,height_,radius_);
        return intersection{t_min,intersectionPoint, normalize(unnormalizedNormal),material.value(),u,v};
    };
    return {};

}

std::optional<std::shared_ptr<AABB>> OpenCylinder::bounding_box() const {
    glm::vec3 axis_normalized = glm::normalize(axis_);

    // 2. Create a rotation matrix that aligns the cylinder axis with the y-axis.
    glm::vec3 y_axis(0.0f, 1.0f, 0.0f); // the target axis
    glm::vec3 rotation_axis = glm::cross(axis_normalized, y_axis);
    float rotation_angle = acos(glm::dot(axis_normalized, y_axis));

    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_angle, rotation_axis);

    // 3. Rotate the base and top points of the cylinder using this matrix.
    glm::vec4 base_rotated = rotation_matrix * glm::vec4(base_, 1.0f);
    glm::vec4 top_rotated = rotation_matrix * glm::vec4(base_ + height_ * axis_, 1.0f);

    // 4. Calculate the AABB as before, but using these rotated points and a vertical axis.
    glm::vec3 min_point = glm::vec3(base_rotated) - glm::vec3(radius_, 0.0f, radius_);
    glm::vec3 max_point = glm::vec3(top_rotated) + glm::vec3(radius_, 0.0f, radius_);

    // 5. Rotate the AABB back to the original orientation using the inverse of the rotation matrix.
    glm::mat4 inverse_rotation_matrix = glm::inverse(rotation_matrix);

    return std::make_shared<AABB>(glm::vec3(inverse_rotation_matrix * glm::vec4(min_point, 1.0f)), glm::vec3(inverse_rotation_matrix * glm::vec4(max_point, 1.0f)));
}
