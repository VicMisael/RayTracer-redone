#pragma once
#include "../../../utils/Types.h"
#include "../Light.h"
class PointLight:public Light
{
protected:
	Point3 location;
	PointLight(const Point3 _location, const float _intensity, const ColorVec _color): Light(_intensity, _color),location(_location) {}

public:
	PointLight() = delete;


};

