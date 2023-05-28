#include "Lambertian.h"
#include "../../utils/Constants.h"
#include <cmath>
#include "../../utils/utility.h"
#include <glm/geometric.hpp>

ColorVec Lambertian::rho(const Vector3& wo) const
{
	return kd_ * cd_;
}

ColorVec Lambertian::f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const 
{
	 return kd_ * cd_ * Constants::INVPI_FLT;
}


sample_f_out Lambertian::sample_f(const intersection& intersection, const Vector3& wo) const
{
	const Vector3 inNormal = intersection.normal;
	//TODO: Explain these magic numbers
	const Vector3 v = cross(Vector3(0.0034, 1.0, 0.0071), inNormal);
	const Vector3 vNormalized = glm::normalize(v);
	const Vector3 u = cross(vNormalized, inNormal);

	//TODO: Improve sampling
	const auto wi=utility::random_in_hemisphere(inNormal);
	const float pdf = dot(inNormal,wi) * Constants::INVPI_FLT;

	return { kd_ * cd_ * Constants::INVPI_FLT,wi,pdf };
 }
