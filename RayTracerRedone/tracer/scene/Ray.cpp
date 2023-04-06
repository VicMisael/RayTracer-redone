#include "Ray.h"

Vector3f Ray::point_at(float t)
{
	return origin + direction * t;
}
