#ifndef _WORLD_
#define _WORLD_
#include <memory>
#include <vector>
#include "../objects/VirtualObject.h"
#include "Canvas.h"
#include "ViewPlane.h"
#include "../utils/intersection_data.h"
#include "light/AmbientLight.h"
#include "light/Light.h"
#include "../utils/sampler/sampler.h"


class World
{
private:
	ColorVec trace_ray(const Ray ray, const int depth) const;
	ColorVec shade(intersection_data, Ray);
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	std::vector<Light*> lights;
	ColorVec bgColor;
	AmbientLight ambient_light;
	sampler *_sampler;
public:

	bool perspective = false;

	World(ViewPlane _viewPlane, 
		std::vector<VirtualObject*> _objects,
		AmbientLight _ambient_light, 
		ColorVec _bgColor,sampler *sampler) :viewPlane(_viewPlane), bgColor(_bgColor),
		ambient_light(_ambient_light),_sampler(sampler)
	{
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}
	
	void render( Canvas*) const;
	intersection_data hit( Ray ray) const;	
	

};
#endif