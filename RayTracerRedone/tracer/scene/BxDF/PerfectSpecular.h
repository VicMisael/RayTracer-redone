#pragma once
#include "BxDF.h"
class PerfectSpecular :
    public BxDF
{
public:
	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f sample_f(const intersection& intersection, const Vector3& wo) const override;
};

