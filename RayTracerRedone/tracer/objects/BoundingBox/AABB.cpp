//
// Created by misae on 30/05/2023.
//

#include "AABB.h"
#include <algorithm>


bool AABB::intersects(const Ray &ray) const {
    float t_min=0;
    float t_max=std::numeric_limits<float>::max();
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.direction[a];
        auto t0 = (min()[a] - ray.origin[a]) * invD;
        auto t1 = (max()[a] - ray.origin[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

bool AABB::intersects(const Ray& ray, float& t_min) const
{
  
    float t_max = std::numeric_limits<float>::max();
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.direction[a];
        auto t0 = (min()[a] - ray.origin[a]) * invD;
        auto t1 = (max()[a] - ray.origin[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;

}
