#include "Lambertian.h"
#include "../../utils/Constants.h"
#include <cmath>

ColorVec Lambertian::rho(const Vector3& wo)
{
	return kd_ * cd_;
}

ColorVec Lambertian::f(const intersection& intersection, const Vector3& wo, const Vector3& wi)
{
	return kd_ * cd_ * Constants::INVPI_FLT;
}

sample_f Lambertian::sample_f(const intersection& intersection, const Vector3& wo)
{

}
