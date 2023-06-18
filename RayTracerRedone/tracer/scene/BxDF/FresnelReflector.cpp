#include "FresnelReflector.h"

float FresnelReflector::total_internal_reflection(const Ray &ray, const intersection &intersection) const {
    return 0;
}

ColorVec FresnelReflector::rho(const Vector3 &wo) const {
    return ColorVec();
}

ColorVec FresnelReflector::f(const intersection &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return ColorVec();
}

sample_f_out FresnelReflector::sample_f(const intersection &intersection, const Vector3 &wo) const {
    return sample_f_out();
}
