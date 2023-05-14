#pragma once
#include "Light.h"


class AmbientLight:public Light
{
public:
	AmbientLight() = delete;
	AmbientLight(const float _intensity, const ColorVec _color) :Light(_intensity, _color) {}
	ColorVec intensityAtPoint(const Point3) const ;
};

