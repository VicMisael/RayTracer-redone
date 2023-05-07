#pragma once
#include <vector>

#include "../../utils/ColorVec.h"

struct scatter_record
{

};
struct Material
{
	ColorVec color;
	Material(ColorVec _color) :color(_color) {};

	// virtual scatter_record scatter(Ray in) = 0;

};

