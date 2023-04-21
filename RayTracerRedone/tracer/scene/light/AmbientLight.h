#pragma once
#include "Light.h"


class AmbientLight:protected Light
{
public:
	AmbientLight(float intensity, ColorVec _color) :Light(intensity, _color){};
};

