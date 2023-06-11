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
                      return a->bounding_box()->min().x < b->bounding_box()->min().x;

                  });
    } else if (axis == 1) {
        std::sort(objects.begin(), objects.end(),
                  [](const std::shared_ptr<VirtualObject>& a, const std::shared_ptr<VirtualObject>& b) {
                      return a->bounding_box()->min().y < b->bounding_box()->min().y;
                  });
    } else {
        std::sort(objects.begin(), objects.end(),
                  [](const std::shared_ptr<VirtualObject>& a, const std::shared_ptr<VirtualObject>& b) {
                      return a->bounding_box()->min().z <  a->bounding_box()->min().z;
                  });
    }
}

std::optional<intersection> BVH::intersects(const Ray &ray) const {
    float t_min = Constants::MAX_FLOAT;
    return BVH::intersects(ray,t_min);
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
        aabb = object->bounding_box();
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

std::shared_ptr<AABB> BVH::bounding_box() const  {
    return this->aabb;
}

std::optional<intersection> BVH::intersects(const Ray &ray, float t_min) const {

    std::optional<intersection> selintersection={};
    if(!unboundables.empty()){
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
    }

    if(aabb==nullptr){
        return selintersection;
    } else{
        float aabb_min=0;
        float aabb_max=t_min;
        auto intersectsaabb=this->aabb->intersects(ray,aabb_min,aabb_max);
        if(!intersectsaabb || aabb_min>t_min){
            return {};
        }
    }
    if(object){
        //Leaf node
        // if this condition is reached left and right are null
        assert(left == nullptr && right == nullptr);
        const auto intersection=object->intersects(ray);
        if(intersection.has_value() && intersection->tmin<t_min){
            t_min=intersection->tmin;
            return object->intersects(ray);
        }else
            return {};
    }
    const auto left_int = left->intersects(ray,t_min);
    if(left_int.has_value()){
        auto temp=*left_int;
        if(temp.tmin<t_min && temp.tmin>0){
            t_min=temp.tmin;
            selintersection.emplace(temp);

        };
    }
    const auto right_int= right->intersects(ray,t_min);
    if(right_int.has_value()){
        auto temp=*right_int;
        if(temp.tmin<t_min && temp.tmin>0){
            selintersection.emplace(temp);
        };
    }
    return selintersection;

}


