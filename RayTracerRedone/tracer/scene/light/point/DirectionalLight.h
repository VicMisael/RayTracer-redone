#pragma once
#include "PointLight.h"

class DirectionalLight:public PointLight
{
public:
	Vector3 direction;
	DirectionalLight() = delete;
	DirectionalLight(const Vector3 _direction,const Point3 _location, const float _intensity, const ColorVec _color) :
	PointLight(_location, _intensity, _color),direction(_direction)
	{}

};

