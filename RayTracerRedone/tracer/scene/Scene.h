#pragma once
#include "Canvas.h"

#include "World.h"
#include <memory>
#include <utility>
class Scene
{
private:
	const World world;
	Canvas* canvas;
public:
	Scene(const World _world, Canvas* _canvas) :world(_world), canvas(_canvas) {};

	void render(const int32_t recursion_depth,std::shared_ptr<sampler> sampler) const
	{
		world.render(canvas, recursion_depth,std::move(sampler));
	}

	void draw() const {
		canvas->draw();
	};
};

