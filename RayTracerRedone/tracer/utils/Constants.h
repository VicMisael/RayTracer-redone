#pragma once
#include <float.h>
#include "Intersection.h"
namespace Constants {
	constexpr float EPSILON=FLT_EPSILON;
	constexpr float MAXFLOAT = std::numeric_limits<float>::max();
	const Intersection NO_INTERSECTION{ false, MAXFLOAT , Vector3(), Vector3() };
}