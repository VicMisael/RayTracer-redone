#pragma once
#include "../objects/VirtualObject.h"
#include "intersection.h"
//Temporary hold for intersectionData
struct intersection_data
{
	bool hit_something=false;
	intersection *intersection = nullptr;
	std::shared_ptr<Material> material;
};

