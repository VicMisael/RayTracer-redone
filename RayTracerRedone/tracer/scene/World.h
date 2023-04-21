#ifndef _WORLD_
#define _WORLD_
#include <vector>
#include <memory>
#include "../objects/VirtualObject.h"
#include "Canvas.h"
#include "ViewPlane.h"
#include "../utils/intersection_data.h"
#include "light/AmbientLight.h"
#include "light/Light.h"

class World
{
private:
	ColorVec trace_ray(const Ray ray, const int depth) const;
	ColorVec compute_lightning(intersection_data, Ray);
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	std::vector<Light*> lights;
	AmbientLight ambient_light;
	ColorVec bgColor;
public:

	bool perspective = false;

	World(ViewPlane _viewPlane, std::vector<VirtualObject*> _objects, AmbientLight _ambient_light, ColorVec _bgColor) :viewPlane(_viewPlane), bgColor(_bgColor),
		ambient_light(_ambient_light) {
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}
	
	void render( Canvas*) const;
	intersection_data hit(const Ray ray) const;	
	

};
#endif