#pragma once
#include "PointLight.h"

class NonDirectionalLight:public PointLight
{
public:
	NonDirectionalLight(const Point3 _location, const float _intensity, const ColorVec _color) :PointLight(_location, _intensity,  _color)  {}
};

