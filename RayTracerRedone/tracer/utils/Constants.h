#pragma once
#include <float.h>
#include "intersection.h"
namespace Constants {
	constexpr float EPSILON=FLT_EPSILON;
	constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
	constexpr intersection NO_INTERSECTION{ false, MAX_FLOAT , Vector3(), Vector3() };
}