#pragma once
#include "Types.h"
struct intersection
{
	const bool hits;
	const float tmin;
	const Point3 closestHitPoint;
	const Vector3 normal;
};

