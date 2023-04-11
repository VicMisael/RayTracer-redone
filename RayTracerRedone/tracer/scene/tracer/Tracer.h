#pragma once
#include "../../utils/Color.h"
#include "../World.h"
class Tracer
{
protected:
	World* world;
public:

	Tracer(World* _world) :world(_world) {};
	virtual Color trace_ray(const Ray ray,const int depth) const =0;
};

