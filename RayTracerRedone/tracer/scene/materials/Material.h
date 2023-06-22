#pragma once
#include <optional>
#include "../../utils/ColorVec.h"
#include "../Ray.h"



class World;
struct intersectionRec;

class Material
{

public:
	virtual ~Material() = default;
    Material()= default;

	virtual ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const = 0;
};

