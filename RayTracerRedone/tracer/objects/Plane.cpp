#include "Plane.h"
#include <glm/geometric.hpp>


glm::vec3 computeU(glm::vec3 normal) {
    glm::vec3 randomVec = glm::vec3(1, 0, 0);
    if (glm::dot(normal, randomVec) > 0.99) // they are too parallel
        randomVec = glm::vec3(0, 1, 0);

    return glm::normalize(glm::cross(normal, randomVec));
}

glm::vec3 computeV(glm::vec3 normal, glm::vec3 u) {
    return glm::cross(normal, u);
}

std::tuple<float,float> computeUV(glm::vec3 pointInPlane, glm::vec3 otherPoint, glm::vec3 normal) {
    glm::vec3 u = computeU(normal);
    glm::vec3 v = computeV(normal, u);

    glm::vec3 delta = otherPoint - pointInPlane;

    float uCoordinate = glm::dot(delta, u);
    float vCoordinate = glm::dot(delta, v);

    return { uCoordinate/100, vCoordinate/100 };
}
std::optional<intersection> Plane::intersects(const Ray &ray) const
{
	using namespace glm;
	const float dot_dir_normal = dot(ray.direction, normal);
	const float t = dot(point - ray.origin, normal) / dot_dir_normal;
	if (t > Constants::EPSILON+0.001f) {
        const auto intersectionPoint=ray.point_at(t);
        const auto [u,v] = computeUV(point, intersectionPoint,normal);
		return intersection{t,ray.point_at(t),normal,material.value(),u,v};
	}
	
	return {};
}

void Plane::transform(Matrix4x4 m) {
        point=Vector3(m*Vector4(point,1));
        normal=Vector3(m*Vector4(point,0));
}
