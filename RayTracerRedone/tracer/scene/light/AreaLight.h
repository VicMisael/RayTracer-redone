//
// Created by Misael on 04/07/2023.
//

#pragma once

#include "VectorialLight.h"
#include "../../objects/VirtualObject.h"

class AreaLight : public VectorialLight {
private:
    std::shared_ptr <VirtualObject> object;
public:
    Vector3 getVector(const Point3 point3) const override;

    Vector3 getVectorNormalized(const Point3 point3) const override;

    ColorVec intensityAtPoint(const Point3 point3) const override;

    bool shadow_hit(const World &world, const Ray &outgoing) const override;


    AreaLight() = default;
};
