#pragma once
#include<memory>
#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../utils/Material.h"
class VirtualObject
{
private:
	std::unique_ptr<Material> material;
public: 
	VirtualObject(Material _material) :material(std::move(_material)) {};
	virtual Intersection intersects(const Ray ray)=0;
};

