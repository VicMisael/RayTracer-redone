#pragma once
#include "BxDF.h"

/**
 * Based on ray tracing from groundUP
 */
class Lambertian :
    public BxDF
{
	//Fraction of light reflected
	const float kd_;
	const ColorVec cd_;
public:
	Lambertian(const float kd, const ColorVec cd) :kd_(kd), cd_(cd)
	{

	};
	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f sample_f(const intersection& intersection, const Vector3& wo) const override;
};

