#pragma once

#pragma once
#include <glm/ext/vector_float3.hpp>  
#include <glm/ext/vector_float4.hpp>  
#include <cstdint>

using Point3 = glm::vec3;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

union RGBA {
    uint32_t rgba;
    struct {
        uint8_t  _r, _g, _b, _a;
    };
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :_r(r), _g(g), _b(b), _a(a) {};
    RGBA(uint32_t _rgba) :rgba(_rgba){};
};