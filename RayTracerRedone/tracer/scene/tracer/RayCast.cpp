#include "RayCast.h"

Color RayCast::trace_ray(const Ray ray, const int depth) const
{
	std::optional<Intersection> intersection=world->hit(ray);
	if (intersection.has_value()) {
		const Intersection intersection_val=intersection.value();
		return intersection_val.material.color;
	}
	else
	{
		return world->bg;	
	}
}
