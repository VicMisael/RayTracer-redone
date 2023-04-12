#pragma once
#include "../utils/Types.h"
#include <tuple>
class ViewPlane
{
public:
	const float hsize;
	const float vsize;
	const float pixelsize;	

	ViewPlane(uint32_t _hsize, uint32_t _vsize, float _pixelsize) :hsize(_hsize), vsize(_vsize), pixelsize(_pixelsize) {}

};

