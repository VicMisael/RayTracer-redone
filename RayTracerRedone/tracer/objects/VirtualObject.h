#pragma once
#include<memory>
#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../utils/Material.h"
class VirtualObject
{
public: 
	virtual Intersection intersects(const Ray ray)=0;
};

