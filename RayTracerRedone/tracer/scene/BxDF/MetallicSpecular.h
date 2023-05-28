#pragma once
#include "BxDF.h"
class MetallicSpecular :
    public BxDF
{
	const ColorVec cr = Constants::WHITE;
	const float kr_;
	const float fuzz_;
public:
	MetallicSpecular(const float kr, const float fuzz) :kr_(kr), fuzz_(fuzz) {};

	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f sample_f(const intersection& intersection, const Vector3& wo) const override;
};

