#include "DirectionalLight.h"

#include <glm/geometric.hpp>

Vector3 DirectionalLight::getVector(const Point3 p) const
{
	return direction_;
}

Vector3 DirectionalLight::getNormalizedDirection(const Point3 p) const
{
	return glm::normalize(getVector(p));
}

ColorVec DirectionalLight::intensityAtPoint(const Point3) const
{
	return this->intensity * this->color;
}
