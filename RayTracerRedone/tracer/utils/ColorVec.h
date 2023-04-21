#pragma once
#include <glm/vec4.hpp>
using namespace glm;
class ColorVec :public vec4
{
public:
	constexpr ColorVec() :vec4(0, 0, 0,1) {};
	constexpr ColorVec(vec4 vec) :vec4(vec) {};
	constexpr ColorVec(float r, float g, float b) :vec4(r, g, b,1.0f) {};
	constexpr ColorVec(float r, float g, float b, float a) :vec4(r, g, b, a) {};
	
};

