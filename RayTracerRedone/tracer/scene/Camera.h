//
// Created by Misael on 05/06/2023.
//

#pragma once
#include "../utils/Types.h"
class Camera {
public:
    Camera(const Vector3 &up, const Vector3 &lookAt, const Vector3 &eye) : up(up), look_at(lookAt), eye(eye) {}

private:
    Vector3 up;
    Vector3 look_at;
    Vector3 eye;

};

