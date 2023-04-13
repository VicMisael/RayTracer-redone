#pragma once
#include <vector>
#include "../objects/VirtualObject.h"
#include "Canvas.h"
#include "ViewPlane.h"
class World
{
public:
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	Color bgColor;
	World(ViewPlane _viewPlane, std::vector<VirtualObject*> _objects, Color _bgColor):viewPlane(_viewPlane),bgColor(_bgColor){
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}
	void render(Canvas *canvas) const;
	std::optional<Intersection> hit(const Ray ray) const;	
	

};

