#include "World.h"
#include <limits>
#include "../utils/Constants.h"
Color trace_ray(const World *world,const Ray ray, const int depth) 
{
	auto intersection = world->hit(ray);
	if (intersection.has_value()) {
		const Intersection intersection_val = intersection.value();
		return intersection_val.material.color;
	}
	else
	{
		return world->bgColor;
	}
}

void World::render(const Canvas* canvas) const
{
	const uint32_t height= canvas->getHeight();
	const uint32_t width = canvas->getWidth();
	const float ystep = canvas->step_size_y(viewPlane);
	const float xstep = canvas->step_size_x(viewPlane);
	const float zw = 100.0f;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			const float vp_y=ystep* y;
			const float vp_x = xstep * x;
			const float y_coord = viewPlane.pixelsize * (vp_y * ystep - 0.5f*(viewPlane.hsize));
			const float x_coord = viewPlane.pixelsize * (vp_x * xstep - 0.5f * (viewPlane.wsize));
			Ray r(Vector3(x_coord,y_coord,zw),Vector3(0,0,-1));
			trace_ray(this,r,0);
		}
	}
}

std::optional<Intersection> World::hit(const Ray ray) const
{

	float tmin = Constants::MAXFLOAT;
	std::optional<Intersection> returned_intersection = {};

	for (VirtualObject* object : objects) {
		auto intersects=object->intersects(ray);
		if (intersects.has_value() && intersects.value().tmin < tmin) {
			tmin = intersects.value().tmin;
			returned_intersection.emplace(intersects.value());
		}
		return returned_intersection;
	}
}
