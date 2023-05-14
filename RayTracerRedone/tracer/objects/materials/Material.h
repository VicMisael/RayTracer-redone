#pragma once
#include <optional>
#include <vector>

#include "../../utils/ColorVec.h"
#include "../../utils/intersection_data.h"
struct scatter_in
{
	Ray in;
	intersection_data intersection_data;

};
struct scatter_out
{
	ColorVec attenuation;
	Ray out;
};
struct Material
{
	virtual ~Material() = default;
	ColorVec color;
	Material(ColorVec _color) :color(_color) {};

	//returns a value if and only if the ray was
	virtual std::optional<scatter_out> scatter(scatter_in in) = 0;
	
};

