#pragma once
#include "../utils/Types.h"
class Ray
{
private:
	Vector3f origin;
	Vector3f direction;
public:
	Ray(Vector3f _origin, Vector3f _direction) :origin(_origin), direction(_direction) {};

	Vector3f point_at(float t);
};

