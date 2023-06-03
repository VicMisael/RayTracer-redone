//
// Created by Misael on 31/05/2023.
//

#include <algorithm>
#include "BVH.h"
#include <iterator>

inline void sort(std::vector<std::shared_ptr<VirtualObject>>& objects){
    int axis = rand() % 3;
    if (axis == 0) {
        std::sort(objects.begin(), objects.end(),
                  [](const std::shared_ptr<VirtualObject>& a, const std::shared_ptr<VirtualObject>& b) {
                      return a->bounding_box().value()->min().x < b->bounding_box().value()->min().x;

                  });
    } else if (axis == 1) {
        std::sort(objects.begin(), objects.end(),
                  [](const std::shared_ptr<VirtualObject>& a, const std::shared_ptr<VirtualObject>& b) {
                      return a->bounding_box().value()->min().y < b->bounding_box().value()->min().y;
                  });
    } else {
        std::sort(objects.begin(), objects.end(),
                  [](const std::shared_ptr<VirtualObject>& a, const std::shared_ptr<VirtualObject>& b) {
                      return a->bounding_box().value()->min().z <  a->bounding_box().value()->min().z;
                  });
    }
}

std::optional<intersection> BVH::intersects(const Ray &ray) const {
    if (!aabb->intersects(ray)) {
        return std::nullopt;
    }

    std::optional<intersection> left_intersection = left ? left->intersects(ray) : std::nullopt;
    std::optional<intersection> right_intersection = right ? right->intersects(ray) : std::nullopt;

    std::optional<intersection> closest_intersection = std::nullopt;
    // Check the closest intersection from the children
    if (left_intersection && (!right_intersection || left_intersection->tmin < right_intersection->tmin)) {
        closest_intersection.emplace(*left_intersection);
    }
    else if (right_intersection) {
        closest_intersection.emplace(*right_intersection);
    }

    // Check intersections with unboundable objects
    for (const auto& obj : unboundables) {
        auto inter = obj->intersects(ray);
        if (inter && (!closest_intersection || inter->tmin < closest_intersection->tmin)) {
            closest_intersection.emplace(*inter);
        }
    }

    return closest_intersection;

}


BVH::BVH( std::vector<std::shared_ptr<VirtualObject>> objectList) {

    //create the copy
    if (objectList.size() == 0) {
        return;
    }
    std::vector<std::shared_ptr<VirtualObject>> objects;
    std::copy_if(objectList.begin(), objectList.end(), std::back_inserter(unboundables),[&]( const std::shared_ptr<VirtualObject>& item ){
        return !item->hasBoundingBox();
    });

    std::copy_if(objectList.begin(), objectList.end(), std::back_inserter(objects), [&](const std::shared_ptr<VirtualObject>& item) {
        return item->hasBoundingBox();
     });

    sort(objects);

    if (objects.size() == 1) {
        object = objects[0];
        aabb = object->bounding_box().value();
    }else if(objects.size()==2)
    {
        left = std::make_unique<BVH>(std::vector<std::shared_ptr<VirtualObject>>{objects[0]});
        right = std::make_unique<BVH>(std::vector<std::shared_ptr<VirtualObject>>{objects[1]});
        aabb = AABB::surrounding_box(left->aabb, right->aabb);
    }else{
        auto middle = objects.begin() + objects.size() / 2;
        std::vector<std::shared_ptr<VirtualObject>> leftObjects(objects.begin(), middle);
        std::vector<std::shared_ptr<VirtualObject>> rightObjects(middle, objects.end());
        left = std::make_unique<BVH>(leftObjects );
        right = std::make_unique<BVH>(rightObjects);
        aabb = AABB::surrounding_box(left->aabb, right->aabb);
    }

}

std::optional<std::shared_ptr<AABB>> BVH::bounding_box() const {
    return this->aabb;
}


