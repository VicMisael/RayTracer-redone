//
// Created by Misael on 04/07/2023.
//

#pragma once

#include "VectorialLight.h"

class AreaLight: public VectorialLight {
public:
    Vector3 getVector(const Point3 point3) const override;

    Vector3 getNormalizedDirection(const Point3 point3) const override;

    ColorVec intensityAtPoint(const Point3 point3) const override;

    bool shadow_hit(const World &world, const Ray &outgoing) const override;

};
