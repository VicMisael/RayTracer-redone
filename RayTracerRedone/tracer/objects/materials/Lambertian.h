#pragma once
#include "Material.h"
class Lambertian :
    public Material
{
public:
	explicit Lambertian(const ColorVec& _color)
		: Material(_color)
	{
	}

	std::optional<scatter_out> scatter(scatter_in in) override;
};

