#pragma once
#include "VirtualObject.h"
class Ball: public VirtualObject
{
public:
	Point3 center;
	float radius;
	Ball(Point3 center, float radius, Material material) :VirtualObject(material), center(center), radius(radius) {};
	std::optional<Intersection> intersects(const Ray ray) const override;
	
};

