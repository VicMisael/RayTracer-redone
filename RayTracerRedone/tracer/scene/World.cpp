#include "World.h"
#include <limits>
#include "../utils/Constants.h"

#include <iostream>

ColorVec World::trace_ray(const Ray ray, const int depth) const
{
	const auto intersection = hit(ray);
	if (intersection.hit_something) {
		return intersection.virtual_object->material.color;
	}
	else
	{
		return bgColor;
	}
}

void World::render(Canvas* canvas) const
{
	const uint32_t height = canvas->getHeight();
	const uint32_t width = canvas->getWidth();
	const float ystep = canvas->step_size_y(viewPlane);
	const float xstep = canvas->step_size_x(viewPlane);
	const float zw = viewPlane.zw;

	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			const float vp_y = ystep * y;
			const float vp_x = xstep * x;
			const float y_coord = -viewPlane.pixelsize * (vp_y - 0.5f * (viewPlane.hsize - 1.0f));
			const float x_coord = viewPlane.pixelsize * (vp_x - 0.5f * (viewPlane.wsize - 1.0f));
			const Ray r(Vector3(x_coord, y_coord, zw), Vector3(0, 0, -1));
			canvas->write_pixel(x, y, ColorRGBA(trace_ray(r, 0)));
		}
	}
}

intersection_data World::hit(const Ray ray) const
{

	float t_min = Constants::MAX_FLOAT;
	intersection_data data;
	for (VirtualObject* object : objects) {
		auto intersects=object->intersects(ray);
		if (intersects.hits && intersects.tmin < t_min) {
			data.hit_something = true;
			t_min = intersects.tmin;
			data.intersection = &intersects;
			data.virtual_object = object;
		}
	}
	return data;
}
