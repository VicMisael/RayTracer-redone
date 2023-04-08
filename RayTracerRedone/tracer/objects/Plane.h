#pragma once

#include "./VirtualObject.h"
class Plane:public VirtualObject
{
public:
	std::optional<Intersection> intersects(const Ray ray) const override;
};

