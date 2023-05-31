#include "Ball.h"
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/exponential.hpp>
std::optional<intersection> Ball::intersects(const Ray& ray) const
{
	const Vector3 ray_direction = ray.direction;
	const float &radius = this->radius;
	const Point3 &center = this->center;

	const Vector3 origin_minus_center = ray.origin - center;
	const float a = glm::dot(ray_direction, ray_direction);
	const float b = 2.0f * glm::dot(origin_minus_center,ray_direction );
	const float c = glm::dot(origin_minus_center, origin_minus_center) - radius * radius;
	const float disc = b*b-4.0f*a*c;
	if (disc < 0.0f) {
		return {};
	}
	const float t1 = (-b + sqrtf(disc)) / (2.0f * a);
	const float t2 = (-b - sqrtf(disc)) / (2.0f * a);
	const float closest = std::min(t1, t2);
	const Vector3 normal = (origin_minus_center + closest * ray_direction) / radius;
	return intersection{ true,closest,ray.point_at(closest),normal,material.value() };
}
