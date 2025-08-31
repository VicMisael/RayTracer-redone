#pragma once
#include "../config/glm_definitions.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>  
#include <glm/ext/vector_float4.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>

using Point3 = glm::vec3;
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix4x4=glm::mat4x4;
using Matrix3x3=glm::mat3x3;

union RGBA {
    uint32_t rgba;
    struct {
        uint8_t  _r, _g, _b, _a;
    };
};


//==============================================================================
// SIMD (SoA - Structure of Arrays) Type Definitions using xsimd
//==============================================================================
#include "xsimd/xsimd.hpp"

namespace xs = xsimd;

// We are fixing the SIMD processing width to 4 floats (128 bits, e.g., SSE)
using batch_type = xs::batch<float>;
using mask_type = xs::batch_bool<float>;
constexpr size_t SIMD_WIDTH = batch_type::size;

// SoA struct holding X, Y, Z components for a packet of 4 vectors/points
struct Vec3_SoA {
    batch_type x, y, z;
};

// Define semantic aliases for our SoA types
using Point3_SoA = Vec3_SoA;
using Vector3_SoA = Vec3_SoA;