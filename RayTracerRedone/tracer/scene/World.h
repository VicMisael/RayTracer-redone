#ifndef _WORLD_
#define _WORLD_
#include <vector>
#include <memory>
#include "../objects/VirtualObject.h"
#include "Canvas.h"
#include "ViewPlane.h"
class Tracer;

class World
{
public:
	Tracer* tracer_ptr;
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	Color bgColor;


	World(ViewPlane _viewPlane, std::vector<VirtualObject*> _objects, Color _bgColor):viewPlane(_viewPlane),bgColor(_bgColor){
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}
	void render(const Canvas*) const;
	std::optional<Intersection> hit(const Ray ray) const;	
	

};
#endif