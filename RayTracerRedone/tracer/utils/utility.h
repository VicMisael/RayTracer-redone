#pragma once

#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/random.hpp>

#include "Constants.h"
#include "Types.h"


namespace utility {
    //static std::mt19937 generator;
    //A counter, for debugging reasons, leave it there
    inline std::mt19937 generator(time(NULL));

    inline Vector3 random() {

        std::uniform_real_distribution<float> dis;
        //std::uniform_int_distribution<float> dist();
        return {dis(generator), dis(generator), dis(generator)};
    }

    inline double random_double() {
        // Returns a random real in [0,1).
        return rand() / (RAND_MAX + 1.0);
    }

    [[maybe_unused]] inline float inversesqrt(float x) {
        return glm::inversesqrt(x);
    }

//	inline float dot_product_intrinsic(Vector3 a, Vector3 b) {
//		__m128 lhs = _mm_set_ps(a.x, a.y, a.z, 0);
//		__m128 rhs = _mm_set_ps(b.x, b.y, b.z, 0);
//		const auto result = _mm_dp_ps(lhs, rhs, 0xFF);
//		return _mm_cvtss_f32(result);
//	};

    inline Vector3 random(float min, float max) {
        std::uniform_real_distribution dis(min, max);
        //std::uniform_int_distribution<float> dist();
        return {dis(generator), dis(generator), dis(generator)};
    }

    inline float random_in_interval(float min, float max) {
        std::uniform_real_distribution dis(min, max);
        return dis(generator);
    }

    inline Vector3 random_in_unit_sphere() {

//		auto r1 = random_double();
//		auto r2 = random_double();
//		auto x = cos(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
//		auto y = sin(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
//		auto z = 1 - r2;
//		return Vector3(x, y, z);

        return glm::sphericalRand(1.0f);
    }

    inline Vector3 random_in_hemisphere(const Vector3 normal) {
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

    inline Vector2 random_unit_square() {
        return {random_in_interval(0, 1), random_in_interval(0, 1)};
    }

    inline Vector3 random_unit_cube() {
        return {random_in_interval(0, 1), random_in_interval(0, 1), random_in_interval(0, 1)};
    }

    inline Vector3 reflect_vector(const Vector3 in, const Vector3 normal) {
        return glm::reflect(in, normal);
        //return in-2*dot(in,normal)*normal;
    }
}

