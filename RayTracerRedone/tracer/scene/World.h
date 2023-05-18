#pragma once

#include <vector>
#include "Canvas.h"
#include "ViewPlane.h"
#include "light/AmbientLight.h"
#include "../utils/sampler/sampler.h"
#include "../objects/VirtualObject.h"


class World
{
private:
	ColorVec trace_ray(const Ray ray, const int depth) const;
	ColorVec shade(const intersection, const Ray,const int depth) const;
	ViewPlane viewPlane;
	std::vector<VirtualObject*> objects;
	std::vector<Light*> lights;
	ColorVec bgColor;
	AmbientLight ambient_light;
	sampler *_sampler;
	unsigned int depth = 16;
	bool perspective_;
public:



	World(ViewPlane _viewPlane, 
		std::vector<VirtualObject*> _objects,
		AmbientLight _ambient_light, 
		ColorVec _bgColor,sampler *sampler) :viewPlane(_viewPlane), bgColor(_bgColor),
		ambient_light(_ambient_light),_sampler(sampler)
	{
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}

	World(ViewPlane _viewPlane,
		std::vector<VirtualObject*> _objects,
		AmbientLight _ambient_light,
		ColorVec _bgColor, 
		sampler* sampler,
		bool _perspective):World(_viewPlane,_objects,_ambient_light, _bgColor,sampler)
	{
		perspective_ = _perspective;
	};

	void render( Canvas*) const;
	std::optional<intersection> hit( Ray ray) const;
	

};