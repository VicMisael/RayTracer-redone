#pragma once

#include <utility>
#include <vector>
#include "Canvas.h"
#include "ViewPlane.h"
#include "light/AmbientLight.h"
#include "../utils/sampler/sampler.h"
#include "../objects/VirtualObject.h"
#include "light/VectorialLight.h"


class World
{
private:

	ColorVec shade(const intersection&, const Ray&,const int32_t depth) const;
	ViewPlane viewPlane;
	std::vector<std::shared_ptr<VirtualObject>> objects_;
	std::vector<std::shared_ptr<VectorialLight>> lights_;
	ColorVec bgColor;
	AmbientLight ambient_light;
	sampler *_sampler;
	bool perspective_{};
public:
	ColorVec trace_ray(const Ray& ray, const int32_t depth) const;


	World(ViewPlane _viewPlane, 
		std::vector<std::shared_ptr<VirtualObject>> _objects,
		AmbientLight _ambient_light, 
		ColorVec _bgColor,sampler *sampler) :viewPlane(_viewPlane), bgColor(_bgColor),
		ambient_light(std::move(_ambient_light)),_sampler(sampler)
	{
		objects_.insert(objects_.end(), _objects.begin(), _objects.end());
	}



	World(ViewPlane _viewPlane,
		std::vector<std::shared_ptr<VirtualObject>> _objects,
		AmbientLight _ambient_light,
		ColorVec _bgColor, 
		sampler* sampler,
		bool _perspective);

	void render(Canvas*, int32_t)  const;
	std::optional<intersection> hit(const Ray &ray) const;

	AmbientLight getAmbientLight() const
	{
		return ambient_light;
	}
};
