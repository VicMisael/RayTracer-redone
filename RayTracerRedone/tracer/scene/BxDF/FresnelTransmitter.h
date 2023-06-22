//
// Created by Misael on 16/06/2023.
//
#pragma once

#include "BTDF.h"

class FresnelTransmitter: public BTDF {
public:
    float total_internal_reflection(const Ray &ray, const intersectionRec &intersection) const override;

    [[maybe_unused]] ColorVec rho(const Vector3 &wo) const override;

    [[nodiscard]] ColorVec f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const override;

    [[nodiscard]] sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo) const override;

};

