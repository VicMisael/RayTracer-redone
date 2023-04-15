#pragma once
#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../utils/Material.h"
#include "../utils/Constants.h"
class VirtualObject
{
public: 
	Material material;
	VirtualObject(Material _material) :material(_material) {  };
	virtual Intersection intersects(const Ray ray) const=0;
};

