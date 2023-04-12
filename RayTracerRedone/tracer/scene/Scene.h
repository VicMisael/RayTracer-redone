#pragma once
#include "World.h"
#include "Canvas.h"
#include <memory>
class Scene
{
private:
	const std::unique_ptr<World> world;
	const std::unique_ptr<Canvas> canvas;
public:
	Scene(World* _world, Canvas* _canvas) :world(_world), canvas(_canvas) {};
};

