//
// Created by Misael on 14/06/2025.
//

#ifndef RAYSOA_H
#define RAYSOA_H

#include "Ray.h"

class RaySoA {
  public:
    struct {
        float x[4], y[4], z[4];
    } origin;

    struct {
      float x[4], y[4], z[4];
    } directions;

    public:
      RaySoA(const Ray rays[4]){

      };

};



#endif //RAYSOA_H
