#include "World.h"
#include <limits>
#include "../utils/Constants.h"

#include <iostream>

ColorVec World::traceray(const Ray ray, const int depth) const
{
	auto intersection = hit(ray);
	if (intersection.hitSomething) {
		return intersection.virtualObject->material.color;
	}
	else
	{
		return bgColor;
	}
}

static float xmin=FLT_MAX, xmax=-FLT_MAX;
static float ymin=FLT_MAX, ymax=-FLT_MAX;

void World::render(Canvas* canvas) const
{
	const uint32_t height= canvas->getHeight();
	const uint32_t width = canvas->getWidth();
	const float ystep = canvas->step_size_y(viewPlane);
	const float xstep = canvas->step_size_x(viewPlane);
	const float zw = 100.0f;

	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			const float vp_y=ystep* y;
			const float vp_x = xstep * x;
			const float y_coord = -viewPlane.pixelsize * (vp_y  - 0.5f * (viewPlane.hsize -1.0f));
			const float x_coord = viewPlane.pixelsize * (vp_x - 0.5f * (viewPlane.wsize-1.0f));
			const Ray r(Vector3(x_coord,y_coord,zw),Vector3(0,0,-1));
			xmin=std::min(xmin,x_coord);
			ymin = std::min(ymin, y_coord);
			xmax = std::max(xmax, x_coord);
			ymax = std::max(ymax, y_coord);
			canvas->write_pixel(x,y,ColorRGBA(traceray(r, 0)));
		}
	}
	std::cout << "XMAX " << xmax << std::endl;
	std::cout << "YMAX " << ymax << std::endl;
	std::cout << "XMIN " << xmin << std::endl;
	std::cout << "YMIN " << ymin << std::endl;
}

IntersectionData World::hit(const Ray ray) const
{

	float tmin = Constants::MAXFLOAT;
	IntersectionData data;
	for (VirtualObject* object : objects) {
		auto intersects=object->intersects(ray);
		if (intersects.hits && intersects.tmin < tmin) {
			data.hitSomething = true;
			tmin = intersects.tmin;
			data.intersection = &intersects;
			data.virtualObject = object;
		}
	}
	return data;
}
