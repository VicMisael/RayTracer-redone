#pragma once
#include <memory>

#include "../utils/intersection.h"
#include "../scene/Ray.h"
#include "materials/Material.h"
#include "../utils/Constants.h"
class VirtualObject
{
public: 
	std::shared_ptr<Material> material;
	VirtualObject(Material _material) 
	{
		material = std::make_shared<Material>(_material);
	};
	virtual intersection intersects(const Ray &ray) const=0;
};

	