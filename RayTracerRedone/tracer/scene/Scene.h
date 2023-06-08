#pragma once
#include "Canvas.h"

#include "World.h"
#include <memory>
#include <utility>
class Scene
{
private:
	World world;
	Canvas* canvas;
public:
	Scene( World &_world, Canvas* _canvas) :world(_world), canvas(_canvas) {};

	void render(const int32_t recursion_depth,const std::shared_ptr<sampler>& sampler)
	{
		world.render(canvas, recursion_depth,sampler);
	}

	void draw() const {
		canvas->draw();
	};
};

