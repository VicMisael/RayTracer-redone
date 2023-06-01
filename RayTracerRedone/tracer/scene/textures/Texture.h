//
// Created by Misael on 31/05/2023.
//

#pragma once

#include "../../utils/ColorVec.h"
#include "../../utils/Types.h"

class Texture {
public:
    Texture()=default;
    [[nodiscard]] virtual ColorVec value(double u, double v, const Point3& p) const = 0;
};


