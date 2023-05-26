#pragma once
#include "BxDF.h"

/**
 * Based on ray tracing from groundUP
 */
class GlossySpecular :
	public BxDF
	
{
	const float ks;
	const ColorVec color;
	const float exp;
public:
	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f sample_f(const intersection& intersection, const Vector3& wo) const override;
};
