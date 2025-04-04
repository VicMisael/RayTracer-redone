//
// Created by Misael on 16/06/2023.
//

#include "FresnelTransmitter.h"

ColorVec FresnelTransmitter::rho(const Vector3 &wo) const {
    return Constants::BLACK;
}

ColorVec FresnelTransmitter::f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return Constants::BLACK;
}

sample_f_out FresnelTransmitter::sample_f(const intersectionRec &intersection, const Vector3 &wo) const {
    Vector3 normal(intersection.normal);
    float cos_thetai = dot(normal, wo);

    float eta = n_out / n_in;

    if (cos_thetai < 0.0f) {  // transmitted ray is outside
        cos_thetai = -cos_thetai;
        normal = -normal;            // reverse direction of normal
        eta = 1.0f / eta;  // invert thetas
    }


    float kr = fresnel(wo, intersection);
    float cos_theta2 = sqrt(kr);
    Vector3 wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * normal;

    float k = 1.0f / (fabs(dot(normal, wt)));
    const float kt = 1 - kr;
    return {(kt / (eta * eta)) * Constants::WHITE * k, wt, 0};
}

float FresnelTransmitter::internal_reflection(const Vector3 &wo, const intersectionRec &intersection) const {
    float cos_thetai = dot(intersection.normal, -wo);
    float eta = n_in/n_out;

    if (cos_thetai < 0.0f) {
        eta = 1.0f / eta;
    }

    return 1.0f - (1.0f - cos_thetai * cos_thetai) / (eta * eta);
}

float FresnelTransmitter::fresnel(const Vector3 &wo, const intersectionRec &intersection) const {
    Vector3 normal = intersection.normal;
    float ndotd = dot(-normal, wo);
    float eta;

    // Determine if the ray is entering or exiting
    if (ndotd < 0.0f) {
        normal = -normal;
        eta = n_out / n_in;
    } else {
        eta = n_in / n_out;
    }

    float cos_theta_i = dot(-normal, wo);
    float sin2_theta_i = std::max(0.0f, 1.0f - cos_theta_i * cos_theta_i);
    float sin2_theta_t = sin2_theta_i / (eta * eta);

    // Check for total internal reflection
    if (sin2_theta_t > 1.0f) {
        return 1.0f; // Full reflection
    }

    float cos_theta_t = sqrt(std::max(0.0f, 1.0f - sin2_theta_t));

    float r_parallel = (eta * cos_theta_i - cos_theta_t) /
                       (eta * cos_theta_i + cos_theta_t);
    float r_perpendicular = (cos_theta_i - eta * cos_theta_t) /
                            (cos_theta_i + eta * cos_theta_t);

    float kr = 0.5f * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

    return kr;
}
