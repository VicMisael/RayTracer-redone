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

	ColorVec shade(const intersection&, const Ray&,const int32_t depth) const;
	ViewPlane viewPlane;
	std::vector<std::shared_ptr<VirtualObject>> objects;
	std::vector<Light*> lights;
	ColorVec bgColor;
	AmbientLight ambient_light;
	sampler *_sampler;
	bool perspective_;
public:
	ColorVec trace_ray(const Ray& ray, const int32_t depth) const;


	World(ViewPlane _viewPlane, 
		std::vector<std::shared_ptr<VirtualObject>> _objects,
		AmbientLight _ambient_light, 
		ColorVec _bgColor,sampler *sampler) :viewPlane(_viewPlane), bgColor(_bgColor),
		ambient_light(_ambient_light),_sampler(sampler)
	{
		objects.insert(objects.end(), _objects.begin(), _objects.end());
	}

	World(ViewPlane _viewPlane,
		std::vector<std::shared_ptr<VirtualObject>> _objects,
		AmbientLight _ambient_light,
		ColorVec _bgColor, 
		sampler* sampler,
		bool _perspective):World(_viewPlane,_objects,_ambient_light, _bgColor,sampler)
	{
		perspective_ = _perspective;
	};

	void render(Canvas*, int32_t)  const;
	std::optional<intersection> hit(const Ray &ray) const;

	AmbientLight getAmbientLight() const
	{
		return ambient_light;
	}
};