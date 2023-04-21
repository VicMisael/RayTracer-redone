#include "Plane.h"
#include <glm/geometric.hpp>
#include "../utils/Constants.h"
intersection Plane::intersects(const Ray &ray) const
{
	using namespace glm;
	const float dot_dir_normal = dot(ray.direction, normal);
	if(abs(dot_dir_normal)>Constants::EPSILON){
		const float t = dot(point - ray.origin, normal) / dot_dir_normal;
		if (t > Constants::EPSILON) {
			return intersection{true,t,ray.point_at(t),normal};
		}
	}
	return Constants::NO_INTERSECTION;
}
