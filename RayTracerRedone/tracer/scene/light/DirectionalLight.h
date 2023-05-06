#pragma once
#include "VectorialLight.h"

class DirectionalLight:VectorialLight
{
	Vector3 direction_;
public:
	DirectionalLight() = delete;
	DirectionalLight(const Vector3 _direction, const float _intensity, const ColorVec _color) :
		VectorialLight( _intensity, _color), direction_(_direction)
	{}
};

