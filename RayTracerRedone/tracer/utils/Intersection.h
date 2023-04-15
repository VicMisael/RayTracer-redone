#pragma once
#include "Types.h"
#include "Material.h"
struct Intersection
{
	const bool hits;
	const float tmin;
	const Point3 closestHitPoint;
	const Vector3 normal;
};

