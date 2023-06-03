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
    float t_min = Constants::MAX_FLOAT;
    std::optional<intersection> selintersection={};

    for (const std::shared_ptr<VirtualObject> &object : unboundables) {
        const auto intersectsoptional=object->intersects(ray);
        if(intersectsoptional){
            const auto &intersects = *intersectsoptional;
            if ( intersects.tmin < t_min && intersects.tmin > 0) {
                t_min = intersects.tmin;
                selintersection.emplace(intersects);
            }
        }
    }

    if(aabb==nullptr || !aabb->intersects(ray)){
        return selintersection;
    }
    if(object){
        //Leaf node
        // if this condition is reached left and right are null;
        return object->intersects(ray);
    }
    const auto left_int = left->intersects(ray);
    const auto right_int= right->intersects(ray);


    if(left_int.has_value() && right_int.has_value()){
         auto temp=((*left_int).tmin<(*right_int).tmin?*left_int:*right_int);
         if(temp.tmin<t_min && temp.tmin>0){
             selintersection.emplace(temp);
         };
    }else if(left_int.has_value()){
        auto temp=*left_int;
        if(temp.tmin<t_min && temp.tmin>0){
            selintersection.emplace(temp);
        };
    }else if(right_int.has_value()){
        auto temp=*right_int;
        if(temp.tmin<t_min && temp.tmin>0){
            selintersection.emplace(temp);
        };
    }

    return selintersection;

}


BVH::BVH( std::vector<std::shared_ptr<VirtualObject>> objectList) {

    //create the copy

    std::vector<std::shared_ptr<VirtualObject>> objects;
    std::copy_if(objectList.begin(), objectList.end(), std::back_inserter(unboundables),[&]( const std::shared_ptr<VirtualObject>& item ){
        return !item->hasBoundingBox();
    });

    std::copy_if(objectList.begin(), objectList.end(), std::back_inserter(objects), [&](const std::shared_ptr<VirtualObject>& item) {
        return item->hasBoundingBox();
     });

    sort(objects);
    if (objects.size() == 0) {
        return;
    }

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


