#pragma once
#include "Color.h"
#include <cstdint>
#include "Types.h"
typedef vec<4, uint8_t, defaultp> bytevec4;
class ColorRGBA:public bytevec4
{
public:

	ColorRGBA(const Color _color) :bytevec4
		(
		_color.r > 1.0f ? 255 : _color.r*255,
		_color.g > 1.0f ? 255 : _color.g*255,
		_color.b > 1.0f ? 255 : _color.b*255,
		_color.a > 1.0f ? 255 : _color.a*255
		) {};
	RGBA toRgba() const {
		return RGBA(r, g, b, a);
	}
};

