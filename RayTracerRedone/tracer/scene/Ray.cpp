#include "Ray.h"

const Vector3 Ray::point_at(float t) const
{
	return origin + direction * t;
}
