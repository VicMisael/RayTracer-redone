#pragma once
#include <float.h>
#include <cmath>

namespace Constants {
	constexpr double pi = 3.14159265358979323846;
	constexpr float EPSILON=FLT_EPSILON;
	constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
	constexpr float INVPI_FLT = 1 / pi;
}