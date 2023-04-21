#pragma once
#include "../../utils/Types.h"
#include "../../utils/ColorVec.h"
class Light
{
protected:
	float intensity;
	ColorVec color;

	Light(const float _intensity, const ColorVec _color) :intensity(_intensity), color(_color) {}
public:

	Light() = delete;
	float getIntensity() const
	{
		return intensity;
	}

	ColorVec getColor() const
	{
		return color;
	}
	ColorVec intensityAtPoint();
};

