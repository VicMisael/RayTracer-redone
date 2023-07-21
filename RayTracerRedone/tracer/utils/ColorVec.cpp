//
// Created by Misael on 23/06/2023.
//
#include "ColorVec.h"
#include <glm/exponential.hpp>

ColorVec ColorVec::powc(float power) const {
    //  return glm::pow(*this, vec4(power));
    return {powf(r, power), powf(g, power), powf(b, power),1.0f};
}
