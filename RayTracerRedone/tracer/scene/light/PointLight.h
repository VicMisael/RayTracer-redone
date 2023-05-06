#pragma once
#include "VectorialLight.h"
class PointLight:public VectorialLight
{
	Vector3 point;
public:
	PointLight() = delete;
	PointLight(const Vector3 _point, const Point3 _location, const float _intensity, const ColorVec _color) :
		VectorialLight(_intensity, _color), point(_point)
	{}
};

