#pragma once
#include <optional>
#include "../Ray.h"
#include "../../utils/ColorVec.h"


struct intersection;

struct scatter_out
{
	ColorVec attenuation;
	Ray out;
};
class Material
{

public:
	const ColorVec color;
	Material(ColorVec _color) :color(_color) {};

	//returns a value if and only if the ray was
	virtual std::optional<scatter_out> scatter(const Ray in,const intersection intersection) = 0;
	
};

