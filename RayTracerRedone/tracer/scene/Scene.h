#pragma once
#include "Canvas.h"

#include "World.h"
#include <memory>
class Scene
{
private:
	const std::unique_ptr<World> world;
	Canvas* canvas;
public:
	Scene(World* _world, Canvas* _canvas) :world(_world), canvas(_canvas) {};

	void render(const int32_t recursion_depth) const
	{
		world->render(canvas, recursion_depth);
	}

	void draw() const {
		canvas->draw();
	};
};

