#pragma once
#include "../utils/Types.h"
#include <tuple>
class ViewPlane
{
public:
	const uint32_t hsize;
	const uint32_t vsize;
	const float pixelsize;	

	ViewPlane(uint32_t _hsize, uint32_t _vsize, float _pixelsize) :hsize(_hsize), vsize(_vsize), pixelsize(_pixelsize) {}

};

