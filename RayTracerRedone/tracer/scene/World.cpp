#include "World.h"
#include <limits>
#include "../utils/Constants.h"
void World::render(Canvas* canvas) const
{
	canvas->
}

std::optional<Intersection> World::hit(const Ray ray) const
{

	float tmin = Constants::MAXFLOAT;
	std::optional<Intersection> returned_intersection = {};

	for (VirtualObject* object : objects) {
		auto intersects=object->intersects(ray);
		if (intersects.has_value() && intersects.value().tmin < tmin) {
			tmin = intersects.value().tmin;
			returned_intersection.swap(intersects);
		}
		return returned_intersection;
	}
}
