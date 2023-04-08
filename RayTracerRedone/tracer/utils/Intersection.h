#pragma once
#include "Types.h"
#include "Color.h"
struct Intersection
{
	const float tmin;
	const Point3 closestHitPoint;
	const Vector3 normal;
	const Color color;
};

