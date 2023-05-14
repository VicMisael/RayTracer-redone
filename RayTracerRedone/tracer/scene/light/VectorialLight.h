#pragma once
#include "Light.h"

class VectorialLight :public Light
{
public:
	VectorialLight(const float _intensity, const ColorVec _color) : Light(_intensity, _color) {};
	virtual Vector3 getVector(const Point3) const = 0;
	virtual Vector3 getNormalizedVector(const Point3) const = 0;
	virtual ColorVec intensityAtPoint(const Point3) const = 0;
};

