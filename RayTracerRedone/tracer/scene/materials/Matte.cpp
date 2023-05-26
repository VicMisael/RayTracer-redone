#include "Matte.h"

#include <glm/geometric.hpp>

#include "../World.h"

ColorVec Matte::shade(const World& world, const Ray& ray, const intersection& intersection, int32_t depth) const
{
	const Vector3 wo = -ray.direction;
	const auto al = world.getAmbientLight();
	ColorVec L = brdf_.rho(wo)*al.intensityAtPoint(intersection.hit_point)*al.getColor();
	for(const auto &light:world.lights())
	{
		const auto wi = light->getNormalizedDirection(intersection.hit_point);
		const float ndotwi = glm::dot(intersection.normal, wi);
		if(ndotwi>0)
		{
			L += brdf_.f(intersection, wo, wi) * light->intensityAtPoint(intersection.hit_point) * ndotwi;
		}
	}

	return L;
}
