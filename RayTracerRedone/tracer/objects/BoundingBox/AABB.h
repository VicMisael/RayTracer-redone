//
// Created by misae on 30/05/2023.
//

#pragma once


#include "../VirtualObject.h"

class AABB: public VirtualObject{
public:
            AABB()=default;
    std::optional<intersection> intersects(const Ray &ray) const override;
};

