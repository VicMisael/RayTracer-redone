#pragma once
#include "Material.h"
#include "../BxDF/Lambertian.h"
#include "../BxDF/GlossySpecular.h"
class Phong :
    public Material
{
	const Lambertian lambertian_;
	const GlossySpecular glossy_specular_;
public:
	Phong(const ColorVec color,const ColorVec specular_color,
		const float ks, const float kd, const float exp) :lambertian_(kd, color), glossy_specular_(ks, specular_color, exp) {};

	Phong(const ColorVec color,const float ks,const float kd,const float exp):lambertian_(kd,color),glossy_specular_(ks,exp){};
	
	Phong(const ColorVec color, const float ks, const float exp) :lambertian_(1.0f, color), glossy_specular_(ks, exp) {};

	ColorVec shade(const World& world, const Ray& ray, const intersection& intersection, int32_t depth) const override;
};

