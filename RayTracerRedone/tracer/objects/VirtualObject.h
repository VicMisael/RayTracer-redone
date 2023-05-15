#pragma once
#include <memory>
#include <optional>

#include "../utils/intersection.h"
#include "../scene/Ray.h"
#include "../scene/materials/Material.h"
#include "../utils/Constants.h"

class VirtualObject
{
public: 
	std::shared_ptr<Material> material;
	VirtualObject(std::shared_ptr<Material> _material) 
	{
		material = _material;
	};
	virtual std::optional<intersection> intersects(const Ray &ray) const=0;
};

	