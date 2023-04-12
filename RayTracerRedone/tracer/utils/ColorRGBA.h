#pragma once
#include "Color.h"
#include <glm/ext/vector_uint4.hpp>
class ColorRGBA_32bit:public glm::uvec4
{
public:
	ColorRGBA_32bit(Color _color) :uvec4
		(
		_color.r > 1.0f ? 255 : _color.r*255,
		_color.g > 1.0f ? 255 : _color.g*255,
		_color.b > 1.0f ? 255 : _color.b*255,
		_color.a > 1.0f ? 255 : _color.a*255
		) {};
};

