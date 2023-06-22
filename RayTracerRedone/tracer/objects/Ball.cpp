#include "Ball.h"
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/exponential.hpp>
#include "../scene/World.h"
#include "../utils/utility.h"

std::tuple<float,float> get_sphere_uv(const Point3 p) {
    // p: a given point on the sphere of radius one, centered at the origin.
    // u: returned value [0,1] of angle around the Y axis from X=-1.
    // v: returned value [0,1] of angle from Y=-1 to Y=+1.
    //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
    //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
    //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

    using namespace Constants;
    const float theta = acosf(-p.y);
    const float phi = atan2f(-p.z, p.x) + Constants::pi;

    const float u = phi / (2*Constants::pi);
    const float v = theta / Constants::pi;
    return {u,v};
}

std::optional<intersectionRec> Ball::intersects(const Ray& ray) const
{
     if(!aabb->intersects(ray)){
        return {};
    }
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
    const auto [u,v]=get_sphere_uv(normal);
	return intersectionRec{closest, ray.point_at(closest), normal, material.value(), u, v };
}

std::shared_ptr<AABB> Ball::bounding_box() const {
    return aabb;
}

void Ball::transform(Matrix4x4 m) {
    center=Vector3(m*Vector4(center,1));
    calculateBoundingBox();
}

Ball::Ball(Point3 _center, float _radius) {
    center=_center;
    radius=_radius;
    class internal:public Material{
        [[nodiscard]] ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override{
            const auto& hitPoint = intersection.hit_point;
            const Ray reflected(hitPoint, utility::reflect_vector(normalize(ray.direction), intersection.normal));
            return 0.5f*world.trace_ray(reflected, depth - 1);
        }
    }  t;
    material=std::make_shared<internal>(t);
    aabb=std::make_shared<AABB>(AABB(
            center - Vector3 (radius, radius, radius),
            center + Vector3(radius, radius, radius)));
}

void Ball::calculateBoundingBox() {
    this->aabb=std::make_shared<AABB>(AABB(
            center - Vector3 (radius, radius, radius),
            center + Vector3(radius, radius, radius)));
}
