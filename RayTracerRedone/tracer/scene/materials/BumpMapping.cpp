//
// Created by Misael on 21/06/2023.
//

#include "BumpMapping.h"
#include "../../utils/Intersection.h"

ColorVec
BumpMapping::shade(const World &world, const Ray &ray, const intersectionRec &intersectionIn, int32_t depth) const {
    auto col = normal_map->value(intersectionIn.u, intersectionIn.v, intersectionIn.hit_point);
    Vector3 normal = intersectionIn.normal;
    const Vector3 bumpMapping = (2.0f * Vector3(col)) - Vector3(1.0f);


    vec3 t;
    vec3 b;

    vec3 c1 = cross(normal, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(normal, vec3(0.0, 1.0, 0.0));

    if (length(c1) > length(c2))
        t = c1;
    else
        t = c2;
    t = normalize(t);
    b = normalize(cross(normal, t));
    normal = mat3(t, b, normal) * bumpMapping;
    auto intersection = intersectionRec{ intersectionIn.tmin, intersectionIn.hit_point, normal, intersectionIn.material,
                                    0, 0 };
    return this->material->shade(world, ray, intersection, depth);

}
