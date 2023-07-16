//
// Created by Misael on 24/06/2023.
//

#include "DiffuseLight.h"
#include "../../utils/utility.h"
#include "../World.h"
ColorVec
DiffuseLight::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    return  intensity*color;
}

DiffuseLight::DiffuseLight(const ColorVec &color, float intensity) : color(color), intensity(intensity) {}
