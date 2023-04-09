#pragma once
#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../utils/Material.h"
#include <optional>
class VirtualObject
{
public: 
	Material material;
	VirtualObject(Material _material) :material(_material) {  };
	virtual std::optional<Intersection> intersects(const Ray ray) const=0;
};

