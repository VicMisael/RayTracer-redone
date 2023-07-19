#pragma once

#include <optional>
#include "../../utils/ColorVec.h"
#include "../Ray.h"


class World;

struct intersectionRec;

class Material {
protected:
    bool castsShadow = true;

public:
    Material() = default;

    virtual ~Material() = default;

    void setcastsShadow(bool casts) {
        castsShadow = casts;
    }

    bool castShadow() const { return castsShadow; }

    virtual ColorVec
    shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const = 0;
};

