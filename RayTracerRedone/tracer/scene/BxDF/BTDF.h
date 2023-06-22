//
// Created by Misael on 16/06/2023.
//

#pragma once

#include "BxDF.h"
#include "../../scene/Ray.h"

class BTDF : public BxDF {
public:
    virtual float total_internal_reflection(const Ray &ray, const intersectionRec &intersection) const= 0;
};


