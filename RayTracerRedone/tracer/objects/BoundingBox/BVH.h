//
// Created by Misael on 31/05/2023.
//

#pragma once

#include "../VirtualObject.h"
#include <vector>
class BVH: public VirtualObject{

private:
    std::shared_ptr<VirtualObject> object;
    std::unique_ptr<BVH> left;
    std::unique_ptr<BVH> right;
    std::shared_ptr<AABB> aabb;
    std::vector<std::shared_ptr<VirtualObject>> unboundables;
    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray, float t_min) const;
public:
     explicit BVH(std::vector<std::shared_ptr<VirtualObject>> objectList);


    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray) const override;

    [[nodiscard]] std::shared_ptr<AABB> bounding_box() const  override;

};

