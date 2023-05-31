#include "Plane.h"
#include <glm/geometric.hpp>
std::optional<intersection> Plane::intersects(const Ray &ray) const
{
	using namespace glm;
	const float dot_dir_normal = dot(ray.direction, normal);
	const float t = dot(point - ray.origin, normal) / dot_dir_normal;
	if (t > Constants::EPSILON+0.001f) {
		return intersection{true,t,ray.point_at(t),normal,material.value()};
	}
	
	return {};
}
