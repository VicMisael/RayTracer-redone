#pragma once
#include "VectorialLight.h"
class PointLight:public VectorialLight
{
	Vector3 point;
public:
	PointLight() = delete;
	PointLight(const Vector3 _point, const float _intensity, const ColorVec _color) :
		VectorialLight(_intensity, _color), point(_point)
	{}

	ColorVec intensityAtPoint( const Point3) const override;
	Vector3 getVector(const Point3) const override;
	Vector3 getNormalizedVector(const Point3) const override;
};

