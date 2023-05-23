#include "Diffuse.h"

#include "../../utils/utility.h"
#include "../../utils/Constants.h"
#include "../World.h"

inline bool nearzero(const Vector3 v)
{
	return v.x < Constants::EPSILON && v.y < Constants::EPSILON && v.z < Constants::EPSILON;
}

inline std::optional<Ray> scatter(const Ray& in, const intersection& intersection)
{
	const auto normal = intersection.normal;
	auto out_dir = normal + utility::random_in_unit_sphere();
	if (nearzero(out_dir))
	{
		out_dir = normal;
	}
	auto scattered = Ray(intersection.hit_point, out_dir);
	return scattered;
}

ColorVec Diffuse::shade(const World& world, const Ray& ray, const intersection& intersection, const int32_t depth) const
{
	const auto& intensity_at_point = world.getAmbientLight().intensityAtPoint(intersection.hit_point);
	const auto& ambient_intensity = intensity_at_point * (color_);
	const auto& out = scatter(ray, intersection);

	if (out.has_value())
	{
		const Ray result = out.value();
		return ambient_intensity + 0.5f * world.trace_ray(result, depth - 1) * color_;
	}
	return ambient_intensity;
}
