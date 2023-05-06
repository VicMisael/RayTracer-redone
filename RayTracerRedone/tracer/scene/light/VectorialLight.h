#pragma once
#include "Light.h"

class VectorialLight :public Light
{
public:
	VectorialLight(const float _intensity, const ColorVec _color) : Light(_intensity, _color) {};
};

