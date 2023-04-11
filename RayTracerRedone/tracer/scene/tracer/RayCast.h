#pragma once
#include "Tracer.h"
class RayCast :public Tracer
{
public:
	RayCast(World* world) :Tracer(world) {};
	Color trace_ray(const Ray ray, const int depth) const final override;
};

