#pragma once
#include "../objects/VirtualObject.h"
#include "Intersection.h"
//Temporary hold for intersectionData
struct IntersectionData
{
	bool hitSomething=false;
	Intersection* intersection = nullptr;
	VirtualObject* virtualObject = nullptr;
};

