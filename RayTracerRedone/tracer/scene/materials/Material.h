#pragma once
#include <optional>
#include "../../utils/ColorVec.h"
#include "../Ray.h"



class World;
struct intersection;

class Material
{

public:
	virtual ~Material() = default;
    Material()= default;

	virtual ColorVec shade(const World& world, const Ray& ray, const intersection& intersection, int32_t depth) const = 0;
};

