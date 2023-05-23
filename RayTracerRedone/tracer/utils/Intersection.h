#pragma once
#include <memory>
#include "Types.h"


class Material;

struct intersection
{
	const bool hits;
	const float tmin;
	const Point3 hit_point;
	const Vector3 normal;
	const std::shared_ptr<Material> material;
};

