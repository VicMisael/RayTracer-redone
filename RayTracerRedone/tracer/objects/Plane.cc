#include "Plane.h"
#include <glm/geometric.hpp>
#include "../utils/Constants.h"
std::optional<Intersection> Plane::intersects(const Ray ray) const
{
	using namespace glm;
	const float t = dot(point - ray.origin, normal) / dot(ray.direction, normal);
	if (t > Constants::EPSILON) {
		return Intersection{t,ray.point_at(t),normal,material};
	}
	return {};
}
