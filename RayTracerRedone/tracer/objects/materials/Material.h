#pragma once
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
};
struct Material
{
	ColorVec color;
	Material(ColorVec _color) :color(_color) {};

	virtual scatter_out scatter(scatter_in in) = 0;

};

