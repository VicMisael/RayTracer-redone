//
// Created by Misael on 31/05/2023.
//

#include "CheckerTexture.h"

ColorVec CheckerTexture::value(double u, double v, const Point3 &p) const {
    auto sines = std::sin(p.x/static_cast<float>(size_))*std::sin(p.y/static_cast<float>(size_))*std::sin(p.z/static_cast<float>(size_));
    if (sines < 0)
        return a_;
    else
        return b_;
}
