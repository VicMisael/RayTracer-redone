#pragma once
#include <memory>
#include <optional>
#include <utility>

#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../scene/materials/Material.h"
#include "../utils/Constants.h"

class VirtualObject
{
public: 
	std::shared_ptr<Material> material;
	explicit VirtualObject(std::shared_ptr<Material> _material)
	{
		material = std::move(_material);
	};
	[[nodiscard]] virtual std::optional<intersection> intersects(const Ray &ray) const =0;
};

	