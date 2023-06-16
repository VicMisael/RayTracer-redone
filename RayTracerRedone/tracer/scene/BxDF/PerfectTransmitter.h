//
// Created by Misael on 16/06/2023.
//

#pragma once
#include "BxDF.h"

class PerfectTransmitter:public BxDF {
public:
    ColorVec rho(const Vector3 &wo) const override;

    ColorVec f(const intersection &intersection, const Vector3 &wo, const Vector3 &wi) const override;

    sample_f_out sample_f(const intersection &intersection, const Vector3 &wo) const override;

};

