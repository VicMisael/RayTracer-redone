#include "World.h"
#include <limits>
#include "../utils/Constants.h"

ColorVec World::trace_ray(const Ray ray, const int depth) const
{
	const auto intersection = hit(ray);
	if (intersection.hit_something) {
		return shade(intersection, ray);
	}
	return bgColor;
	
}

ColorVec World::shade(const intersection_data intersection_data,const Ray ray) const 
{
	const auto intensityatpoint = ambient_light
		.intensityAtPoint(intersection_data.intersection->closestHitPoint);
	return intensityatpoint*(intersection_data.material->color);
}

void World::render(Canvas* canvas) const
{
	const uint32_t height = canvas->getHeight();
	const uint32_t width = canvas->getWidth();
	const float ystep = canvas->step_size_y(viewPlane);
	const float xstep = canvas->step_size_x(viewPlane);
	const float zw = viewPlane.zw;
	const auto  &points = _sampler->generate_points();
	const auto num_samples = _sampler->num_samples;
	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			ColorVec colorVec(0,0,0);
			for (const std::tuple<float, float>& sample_point : points) {
				auto [x_sample_point, y_sample_point] = sample_point;
				const float vp_y =  ystep * y;
				const float vp_x =  xstep * x;

				x_sample_point *= xstep;
				y_sample_point *= ystep;

				if (perspective) {
					const float y_coord = viewPlane.pixelsize * (vp_y - 0.5f * (viewPlane.hsize - 1.0f));
					const float x_coord = -viewPlane.pixelsize * (vp_x - 0.5f * (viewPlane.wsize - 1.0f));
					const Vector3 vp_r(x_coord+ x_sample_point, y_coord+ y_sample_point, zw);
					const Point3 origin(0, 0, 0);
					const Vector3 direction = origin - vp_r;
					const Ray r(origin, direction);
					colorVec += trace_ray(r,0);
					//canvas->write_pixel(x, y, ColorRGBA(trace_ray(r, 0)));
				}
				else {
					const float y_coord = viewPlane.pixelsize * (vp_y - 0.5f * (viewPlane.hsize - 1.0f));
					const float x_coord = viewPlane.pixelsize * (vp_x - 0.5f * (viewPlane.wsize - 1.0f));
					const Vector3 vp_r(x_coord+x_sample_point, -y_coord+y_sample_point, zw);
					const Ray r(vp_r, Vector3(0, 0, -1));
					colorVec += trace_ray(r, 0);
					//canvas->write_pixel(x, y, ColorRGBA(trace_ray(r, 0)));
				}
			}
			const ColorVec out = (colorVec * 1.0f/static_cast<float>(num_samples));
			canvas->write_pixel(x, y,ColorRGBA(out));
		}
	}
}

intersection_data World::hit(const Ray ray) const
{

	float t_min = Constants::MAX_FLOAT;
	intersection_data data;
	for (VirtualObject* object : objects) {
		auto intersects=object->intersects(ray);
		//intersects.tmin > 0
		if (intersects.hits && intersects.tmin < t_min && intersects.tmin > 0) {
			data.hit_something = true;
			t_min = intersects.tmin;
			data.intersection = &intersects;
			data.material = object->material;
		}
	}
	return data;
}
