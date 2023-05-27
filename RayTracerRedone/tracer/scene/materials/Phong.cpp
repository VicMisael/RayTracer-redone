#include "Phong.h"

#include <glm/geometric.hpp>

#include "../World.h"

ColorVec Phong::shade(const World& world, const Ray& ray, const intersection& intersection, int32_t depth) const
{
	const Vector3 wo = -ray.direction;
	const auto al = world.getAmbientLight();
	ColorVec L = lambertian_.rho(wo) * al.intensityAtPoint(intersection.hit_point) * al.getColor();
	for (const auto& light : world.lights())
	{
		const auto wi = light->getNormalizedDirection(intersection.hit_point);
		const float ndotwi = glm::dot(intersection.normal, wi);
		if (ndotwi > 0)
		{
			bool inshadow = false;
			if (light->casts_shadow())
				inshadow = light->shadow_hit(world, Ray(intersection.hit_point, wi));

			if (!inshadow){
				const auto l_intensity = light->intensityAtPoint(intersection.hit_point);
				L += (glossy_specular_.f(intersection, wo, wi)+lambertian_.f(intersection, wo, wi)) * l_intensity * ndotwi;
			}
		}
	}
	//Scoped
	{
		const auto [color, wi, pdf] = lambertian_.sample_f(intersection, wo);
		const float ndotwi = glm::dot(intersection.normal, wi);
		const Ray reflected(intersection.hit_point, wi);

		L += color * world.trace_ray(reflected, depth - 1) * ndotwi / pdf;
	}
	return L;
}
