//
// Created by Misael on 16/06/2023.
//

#include "FresnelTransmitter.h"

ColorVec FresnelTransmitter::rho(const Vector3 &wo) const {
    return ColorVec();
}

ColorVec FresnelTransmitter::f(const intersection &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return ColorVec();
}

sample_f_out FresnelTransmitter::sample_f(const intersection &intersection, const Vector3 &wo) const {
    return sample_f_out();
}

float FresnelTransmitter::total_internal_reflection(const Ray &ray, const intersection &intersection) const {
    return 0;
}
