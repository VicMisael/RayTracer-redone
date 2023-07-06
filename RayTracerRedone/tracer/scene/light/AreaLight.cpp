//
// Created by Misael on 04/07/2023.
//

#include "AreaLight.h"

Vector3 AreaLight::getVector(const Point3 point3) const {
    return Vector3();
}

Vector3 AreaLight::getVectorNormalized(const Point3 point3) const {
    return Vector3();
}

ColorVec AreaLight::intensityAtPoint(const Point3 point3) const {
    return ColorVec();
}

bool AreaLight::shadow_hit(const World &world, const Ray &outgoing) const {
    return false;
}
