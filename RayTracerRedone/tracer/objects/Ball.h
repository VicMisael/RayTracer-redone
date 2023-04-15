#pragma once
#include "VirtualObject.h"
class Ball: public VirtualObject
{
public:
	Point3 center;
	float radius;
	Ball(Point3 _center, float _radius, Material _material) :VirtualObject(_material), center(_center), radius(_radius) {};
	Intersection intersects(const Ray ray) const override;
	
};

