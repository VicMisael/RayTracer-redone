#pragma once
#include "Types.h"
#include "Color.h"
#include "Material.h"
struct Intersection
{
	const float tmin;
	const Point3 closestHitPoint;
	const Vector3 normal;
	const Material material;
};

