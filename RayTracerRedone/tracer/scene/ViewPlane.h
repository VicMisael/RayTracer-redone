#pragma once
#include "../utils/Types.h"
#include <tuple>
class ViewPlane
{
private:
	const float _aspectratioy;
	const float _aspectratiox;
public:
	const uint32_t hsize;
	const uint32_t vsize;
	const float pixelsize;	
	ViewPlane(uint32_t _hsize, uint32_t _vsize, float _pixelsize) :hsize(_hsize), vsize(_vsize), pixelsize(_pixelsize),_aspectratiox(1.0f*_hsize/_vsize)
		,_aspectratioy( _vsize*1.0f / _hsize) {}

};

