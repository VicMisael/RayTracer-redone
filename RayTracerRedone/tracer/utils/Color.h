#pragma once
#include <glm/vec4.hpp>
using namespace glm;
class Color:public vec4
{
public:
	constexpr Color() :vec4(0, 0, 0,1) {};
	constexpr Color(float r, float g, float b) :vec4(r, g, b,1.0f) {};
	constexpr Color(float r, float g, float b, float a) :vec4(r, g, b, a) {};
	
};

