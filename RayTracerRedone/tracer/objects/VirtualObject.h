#pragma once
#include <memory>
#include <optional>
#include <utility>

#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../scene/materials/Material.h"
#include "../utils/Constants.h"

#include "BoundingBox/AABB.h"

class VirtualObject
{
public: 
	std::optional<std::shared_ptr<Material>> material;
    explicit VirtualObject()= default;
	explicit VirtualObject(std::shared_ptr<Material> _material)
	{
		material = std::move(_material);
	};
	[[nodiscard]] virtual std::optional<intersection> intersects(const Ray &ray) const =0;
    virtual std::optional<AABB> bounding_box() const;

};

	