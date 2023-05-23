#pragma once
#include "Material.h"

class Diffuse :
	public Material
{
	const ColorVec color_;

public:
	const ColorVec color;
	explicit Diffuse(const ColorVec& _color)
		: color_(_color)
	{
	}


	ColorVec shade(const World& world, const Ray& ray, const intersection& intersection, int32_t depth) const override;
};
