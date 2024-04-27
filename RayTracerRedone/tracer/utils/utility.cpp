//
// Created by Misael on 15/07/2023.
//
#include "utility.h"

#include <glm/gtx/norm.hpp>


std::mt19937 generator(time(NULL));

Vector3 utility::random() {

    std::uniform_real_distribution<float> dis;
    //std::uniform_int_distribution<float> dist();
    return {dis(generator), dis(generator), dis(generator)};
}

double utility::random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

[[maybe_unused]] float utility::inversesqrt(float x) {
    return glm::inversesqrt(x);
}

//	float dot_product_intrinsic(Vector3 a, Vector3 b) {
//		__m128 lhs = _mm_set_ps(a.x, a.y, a.z, 0);
//		__m128 rhs = _mm_set_ps(b.x, b.y, b.z, 0);
//		const auto result = _mm_dp_ps(lhs, rhs, 0xFF);
//		return _mm_cvtss_f32(result);
//	};

Vector3 utility::random(float min, float max) {
    std::uniform_real_distribution dis(min, max);
    //std::uniform_int_distribution<float> dist();
    return {dis(generator), dis(generator), dis(generator)};
}

Vector3 utility::ONBTransform(Vector3 W, Vector3 in)
{
    W = glm::normalize(W);
    const Vector3 a =
        glm::length2(glm::abs(W) - Vector3(0, 1, 0)) < glm::epsilon<float>() ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
    const Vector3 U = normalize(cross(W, a));
    const Vector3 V = normalize(cross(W, U));
    const Matrix3x3 UVW = Matrix3x3(U, V, W);
    auto result= UVW * in;
    return result;
}

float utility::random_in_interval(float min, float max) {
    std::uniform_real_distribution dis(min, max);
    return dis(generator);
}

Vector3 utility::random_in_unit_sphere() {


    return glm::sphericalRand(1.0f);
}

Vector3 utility::random_in_hemisphere() {
   return random_in_hemisphere( Vector3(0, 1, 0));
}
Vector3 utility::random_in_hemisphere(const Vector3 normal) {
    Vector3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    return -in_unit_sphere;
}


float utility::clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
//Only on Dark Scenes, FAlse positives on Bright ones
 bool utility::nanBugCheck(glm::vec4 _color) {
    const uint8_t r = _color.r > 1.0f ? 255 : _color.r * 255;
    const uint8_t g = _color.g > 1.0f ? 255 : _color.g * 255;
    const uint8_t b = _color.b > 1.0f ? 255 : _color.b * 255;

    if(r==255 && g==255 && b==255){
        printf(" R %f ",_color.r);
        printf(" G %f ",_color.g);
        printf(" B %f \n",_color.b);
        if(std::isnan(_color.r)||std::isnan(_color.g)||std::isnan(_color.b)){
            printf("SHOULD BE HERE");
        }
        if (std::isnan(-_color.r)||std::isnan(-_color.r)||std::isnan(-_color.b)){
            printf("NOT HERE");
        }
        return false;
    }
    return true;
}
Vector2 utility::random_unit_square() {
    return {random_in_interval(0, 1), random_in_interval(0, 1)};
}

Vector3 utility::random_unit_cube() {
    return {random_in_interval(0, 1), random_in_interval(0, 1), random_in_interval(0, 1)};
}

Vector3 utility::reflect_vector(const Vector3 in, const Vector3 normal) {
    return glm::reflect(in, normal);
    //return in-2*dot(in,normal)*normal;
}