#include "Mirror.h"

#include "../World.h"
#include "../../utils/utility.h"

bool hasReflected(const Vector3& dir, const Vector3& normal)
{
	return true || dot(dir, normal) > 0;
};

ColorVec Mirror::shade(const World& world, const Ray& ray, const intersection& intersection, const int32_t depth) const
{
	const auto& hitPoint = intersection.hit_point;
	const Ray reflected(hitPoint, utility::reflect_vector(ray.direction, intersection.hit_point));
	if (hasReflected(reflected.direction, intersection.normal))
	{
		return reflectivity_ * (world.trace_ray(reflected, depth - 1));
	}
	return {0, 0, 0};
}
