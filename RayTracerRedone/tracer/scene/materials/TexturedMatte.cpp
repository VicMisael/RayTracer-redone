//
// Created by Misael on 31/05/2023.
//

#include "TexturedMatte.h"

ColorVec
TexturedMatte::shade(const World &world, const Ray &ray, const intersection &intersection, int32_t depth) const {
    return texture_->value(intersection.u,intersection.v,intersection.hit_point) * Matte::shade(world, ray, intersection, depth);
}