#pragma once
#include <memory>
#include "Types.h"


class Material;

struct intersection
{
	const float tmin;
	const Point3 hit_point;
	const Vector3 normal;
	const std::shared_ptr<Material> material;
    const float u=0;
    const float v=0;
};

