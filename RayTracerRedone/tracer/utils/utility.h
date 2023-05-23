#pragma once
#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Types.h"

namespace utility
{
	//static std::mt19937 generator;
	inline std::mt19937 generator(time(NULL));
	inline Vector3 random()
	{
		
		std::uniform_real_distribution<float> dis;
		//std::uniform_int_distribution<float> dist();
		return { dis(generator), dis(generator), dis(generator) };
	}

	inline Vector3 random(float min,float max)
	{
		std::uniform_real_distribution dis(min,max);
		//std::uniform_int_distribution<float> dist();
		return { dis(generator), dis(generator), dis(generator) };
	}
	inline float random_in_interval(float min, float max)
	{
		std::uniform_real_distribution dis(min, max);
			return dis(generator);
	}
	inline Vector3 random_in_unit_sphere()
	{
		while (true) {
			auto p = random(-1, 1);
			
			auto sqrd_length = length(p) * length(p);
			if (sqrd_length >= 1) continue;
			return p;
		}
	}

	inline Vector3  reflect_vector(const Vector3 in, const Vector3 normal)
	{
		return in-2*dot(in,normal)*normal;
	}
}

