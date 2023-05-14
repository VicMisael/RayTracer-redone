#pragma once
#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Types.h"

namespace utility
{
	//static std::mt19937 generator;
	inline std::mt19937 generator(time(NULL));
	Vector3 random()
	{
		
		std::uniform_real_distribution<float> dis;
		//std::uniform_int_distribution<float> dist();
		return { dis(generator), dis(generator), dis(generator) };
	}

	Vector3 random(float min,float max)
	{
		std::uniform_real_distribution dis(min,max);
		//std::uniform_int_distribution<float> dist();
		return { dis(generator), dis(generator), dis(generator) };
	}

	inline Vector3  reflect_vector(const Vector3f in, const Vector3f normal)
	{
		return in-2*glm::dot(in,normal)*normal;
	}
}

