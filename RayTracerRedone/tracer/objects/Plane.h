#pragma once

#include "VirtualObject.h"
#include "glm/geometric.hpp"
class Plane:public VirtualObject
{
public:
	Point3 point;
	Vector3 normal;
	Plane(Point3 _point,Vector3 _normal,Material _material) :VirtualObject(_material),normal(glm::normalize(_normal)), point(_point) {};
	intersection intersects(const Ray &ray) const override;
};

