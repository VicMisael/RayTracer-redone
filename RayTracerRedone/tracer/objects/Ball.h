#pragma once
#include "VirtualObject.h"
class Ball:VirtualObject
{
private:
	Vector3f center;
	float radius;
public:

	 Intersection intersects(const Ray ray) override;
};

