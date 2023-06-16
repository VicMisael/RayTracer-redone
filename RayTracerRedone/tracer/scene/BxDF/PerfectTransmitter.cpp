//
// Created by Misael on 16/06/2023.
//

#include "PerfectTransmitter.h"

ColorVec PerfectTransmitter::rho(const Vector3 &wo) const {
    return ColorVec();
}

ColorVec PerfectTransmitter::f(const intersection &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return ColorVec();
}

sample_f_out PerfectTransmitter::sample_f(const intersection &intersection, const Vector3 &wo) const {
    return sample_f_out();
}
