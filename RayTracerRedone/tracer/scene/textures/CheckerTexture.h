#pragma once


#include "Texture.h"
#include "Constants.h"

class CheckerTexture: public Texture{
    const ColorVec a_;
    const ColorVec b_;
    const float size_=10;
public:
    CheckerTexture():a_(Constants::RED),b_(Constants::WHITE){};
    explicit CheckerTexture(const float size):size_(size){};
    CheckerTexture(const ColorVec a,const ColorVec b):a_(a),b_(b){

    }
    CheckerTexture(const ColorVec a,const ColorVec b,const float size):a_(a),b_(b),size_(size){

    }
    [[nodiscard]] ColorVec value(double u, double v, const Point3& p) const override;
};



