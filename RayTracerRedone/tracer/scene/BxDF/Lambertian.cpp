#include "Lambertian.h"
#include "../../utils/OrthonormalBase.h"
#include "../../utils/utility.h"
#include <glm/geometric.hpp>

ColorVec Lambertian::rho(const Vector3 &wo) const {
    return kd_ * cd_;
}

ColorVec Lambertian::f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return kd_ * cd_ * Constants::INVPI_FLT;
}


sample_f_out Lambertian::sample_f(const intersectionRec &intersection, const Vector3 &wo) const {
    const Vector3 inNormal = intersection.normal;

    OrthonormalBase orthonormalBase(inNormal);
//    const Vector3 v = cross(Vector3(0.0034, 1.0, 0.0071), inNormal);
//    const Vector3 vNormalized = glm::normalize(v);
//    const Vector3 u = cross(vNormalized, inNormal);
    //TODO: Improve sampling
    auto wi = utility::random_in_hemisphere(inNormal);
//    const auto uvw=Matrix3x3(u, vNormalized, inNormal);
    wi = orthonormalBase.onb() * wi;
    const float pdf = dot(inNormal, wi) * Constants::INVPI_FLT;

    return {kd_ * cd_ * Constants::INVPI_FLT, wi, pdf};
}
