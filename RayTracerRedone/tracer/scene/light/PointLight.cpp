#include "PointLight.h"
#include <glm/geometric.hpp>

inline float distanceAtenuation(float vectorLength)
{
	return glm::inversesqrt(vectorLength);
}

ColorVec PointLight::intensityAtPoint(const Point3 p) const
{
	return distanceAtenuation(glm::length(getVector(p)))*intensity * color;
}

Vector3 PointLight::getVector(const Point3 p) const
{
	return p - point;
}

Vector3 PointLight::getNormalizedDirection(const Point3 p) const
{
	return normalize(PointLight::getVector(p));
}

