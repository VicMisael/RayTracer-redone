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
    const Vector3 w = intersection.normal;


     
    OrthonormalBase orthonormalBase(w);
    auto wi = utility::random_in_hemisphere();
    wi = orthonormalBase.onb() * wi;
    
    const float pdf = dot(w, wi) * Constants::INVPI_FLT;

    return {kd_ * cd_ * Constants::INVPI_FLT, wi, pdf};
}


