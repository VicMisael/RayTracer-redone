#pragma once
#include "../utils/intersection.h"
#include "../scene/Ray.h"
#include "materials/Material.h"
#include "../utils/Constants.h"
class VirtualObject
{
public: 
	Material material;
	VirtualObject(Material _material) :material(_material) {  };
	virtual intersection intersects(const Ray &ray) const=0;
};

