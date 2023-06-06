#pragma once
#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Constants.h"
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

	inline double random_double() {
		// Returns a random real in [0,1).
		return rand() / (RAND_MAX + 1.0);
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
		auto r1 = random_double();
		auto r2 = random_double();
		auto x = cos(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
		auto y = sin(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
		auto z = 1 - r2;
		return Vector3(x, y, z);
	}

	inline Vector3 random_in_hemisphere(const vec3& normal) {
		Vector3 in_unit_sphere = random_in_unit_sphere();
		if (dot(in_unit_sphere, normal) > 0.0) 
			return in_unit_sphere;
        return -in_unit_sphere;
	}

    inline float clamp(float x, float min, float max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

	inline Vector3  reflect_vector(const Vector3 in, const Vector3 normal)
	{
        return glm::reflect(in,normal);
		//return in-2*dot(in,normal)*normal;
	}
}

