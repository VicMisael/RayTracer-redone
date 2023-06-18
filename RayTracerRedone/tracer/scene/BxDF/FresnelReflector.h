#pragma once
#include "BTDF.h"
class FresnelReflector :
    public BTDF
{
public:

    float total_internal_reflection(const Ray& ray, const intersection& intersection) const override;

    [[maybe_unused]] ColorVec rho(const Vector3& wo) const override;

    [[nodiscard]] ColorVec f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const override;

    [[nodiscard]] sample_f_out sample_f(const intersection& intersection, const Vector3& wo) const override;
};

