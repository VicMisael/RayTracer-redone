//
// Created by misae on 30/05/2023.
//

#pragma once
#include "../../scene//Ray.h"
#include "../../utils/Types.h"
class AABB{
    const Point3 min_;
    const Point3 max_;
public:
    AABB()=delete;
    AABB(const Point3 min,const Point3 max):min_(min),max_(max){};

    bool intersects(const Ray &ray, float t_min, float t_max) const;

    AABB surrounding_box() const;

    Point3 min() const {
        return min_;
    }
    [[nodiscard]] Point3 max() const {
        return max_;
    }
};

