#pragma once
#include <float.h>
#include <glm/ext/scalar_constants.hpp> 
#include <cmath>

namespace Constants {
	constexpr double pi = glm::pi<double>();
	
	constexpr float EPSILON=FLT_EPSILON;
	constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
	constexpr float INVPI_FLT = 1 / pi;

	constexpr ColorVec YELLOW(1, 1, 0);
	constexpr ColorVec BLACK(0,0,0);
	constexpr ColorVec WHITE(1, 1, 1);
}