#ifndef _WORLD_
#define _WORLD_
#include <vector>
#include <memory>
#include "../objects/VirtualObject.h"
#include "Canvas.h"
#include "ViewPlane.h"
#include "../utils/intersection_data.h"

class World
{
private:
	ColorVec trace_ray(const Ray ray, const int depth) const;
public:
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	ColorVec bgColor;

	World(ViewPlane _viewPlane, std::vector<VirtualObject*> _objects, ColorVec _bgColor):viewPlane(_viewPlane),bgColor(_bgColor){
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}

	
	void render( Canvas*) const;
	intersection_data hit(const Ray ray) const;	
	

};
#endif