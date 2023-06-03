#pragma once

#include <utility>
#include <vector>
#include "Canvas.h"
#include "ViewPlane.h"
#include "light/AmbientLight.h"
#include "../utils/sampler/sampler.h"
#include "../objects/VirtualObject.h"
#include "light/VectorialLight.h"
#include "../objects/BoundingBox/BVH.h"


class World
{
private:

	ColorVec shade(const intersection&, const Ray&,const int32_t depth) const;
	std::shared_ptr<ViewPlane> viewPlane;
	std::vector<std::shared_ptr<VirtualObject>> objects_;
	std::vector<std::shared_ptr<VectorialLight>> lights_;
	ColorVec bgColor;
	AmbientLight ambient_light;
	sampler *_sampler;
	BVH bvh;
	bool perspective_{};
public:
	ColorVec trace_ray(const Ray& ray, const int32_t depth) const;


	World(std::shared_ptr<ViewPlane> _viewPlane,
		std::vector<std::shared_ptr<VirtualObject>> _objects,
		std::vector<std::shared_ptr<VectorialLight>> lights,
		AmbientLight _ambient_light, 
		ColorVec _bgColor,sampler *sampler,bool perspective) :
		viewPlane(_viewPlane),
		bvh(_objects),
		objects_(_objects),
		lights_(std::move(lights)),
		bgColor(_bgColor),
		ambient_light(std::move(_ambient_light)),_sampler(sampler),perspective_(perspective)
	{
	}



	void render(Canvas*, int32_t)  const;
	std::optional<intersection> hit(const Ray &ray) const;

	std::vector<std::shared_ptr<VectorialLight>> lights() const
	{
		return lights_;
	}

	std::vector<std::shared_ptr<VirtualObject>> objects() const
	{
		return objects_;
	}


	AmbientLight getAmbientLight() const
	{
		return ambient_light;
	}
};
