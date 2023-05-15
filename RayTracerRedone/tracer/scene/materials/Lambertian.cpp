#include "Lambertian.h"
#include "../../utils/utility.h"
#include "../../utils/Constants.h"

bool nearzero(const Vector3 v)
{
	return  v.x < Constants::EPSILON && v.y < Constants::EPSILON && v.z < Constants::EPSILON;
}

std::optional<scatter_out> Lambertian::scatter(const Ray in, const intersection intersection)
{
	const auto normal= intersection.normal;
	auto out_dir = normal + utility::random_in_unit_sphere();
	if (nearzero(out_dir))
	{
		out_dir = normal;
	}
	auto scattered = Ray(intersection.closestHitPoint,out_dir);
	const scatter_out scatter = { color,scattered };
	return scatter;


}
