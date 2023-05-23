#pragma once
#include "Material.h"

class Mirror :
	public Material
{
	const float reflectivity_;

public:
	Mirror(): reflectivity_(1.0f)
	{
	};
	ColorVec shade(const World& world, const Ray& ray, const intersection& intersection,
	               int32_t depth) const override;
};
