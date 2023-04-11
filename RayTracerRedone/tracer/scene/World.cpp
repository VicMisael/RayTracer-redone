#include "World.h"

void World::add_object(VirtualObject* object)
{
	objects.push_back(object);
}

void World::render(void) const
{
}

std::optional<Intersection> World::hit(const Ray ray) const
{
	return std::optional<Intersection>();
}
