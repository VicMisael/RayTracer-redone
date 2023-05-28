#pragma once
#include "BxDF.h"

class PerfectSpecular :
    public BxDF
{
	ColorVec cr = Constants::WHITE;
	const float kr;
public:
	PerfectSpecular(const float kr_):kr(kr_){}

	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f sample_f(const intersection& intersection, const Vector3& wo) const override;
};

