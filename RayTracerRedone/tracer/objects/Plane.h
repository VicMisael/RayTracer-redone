#pragma once

#include "VirtualObject.h"
class Plane:public VirtualObject
{
public:
	Point3 point;
	Vector3 normal;
	Plane(Point3 _point,Vector3 _normal,Material _material) :VirtualObject(_material),normal(_normal), point(_point) {};
	std::optional<Intersection> intersects(const Ray ray) const override;
};

