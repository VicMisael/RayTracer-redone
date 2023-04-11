#pragma once
#include <vector>
#include "../objects/VirtualObject.h"
#include "ViewPlane.h"
class World
{
public:
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	Color bg;
	void add_object(VirtualObject*);
	void render(void) const;
	std::optional<Intersection> hit(const Ray ray) const;
};

