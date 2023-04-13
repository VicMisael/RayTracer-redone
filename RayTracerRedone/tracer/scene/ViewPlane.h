#pragma once
#include "../utils/Types.h"
#include <tuple>
class ViewPlane
{
public:
	const float wsize;
	const float hsize;
	const float pixelsize;	

	ViewPlane(uint32_t _hsize, uint32_t _vsize, float _pixelsize) :wsize(_hsize), hsize(_vsize), pixelsize(_pixelsize) {}

};

