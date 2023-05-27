#include "PointLight.h"
#include "../Ray.h"
#include "../World.h"

#include <glm/geometric.hpp>

inline float distanceAtenuation(float vectorLength)
{
	return glm::inversesqrt(vectorLength);
}

ColorVec PointLight::intensityAtPoint(const Point3 p) const
{
	return inversesqrt(length(getVector(p)))*intensity * color;
}

Vector3 PointLight::getVector(const Point3 p) const
{
	return point-p;
}

Vector3 PointLight::getNormalizedDirection(const Point3 p) const
{
	return normalize(PointLight::getVector(p));
}

bool PointLight::shadow_hit(const World& world, const Ray& outgoing) const
{
	float distance = length(outgoing.origin - this->point);

	for (const auto& obj : world.objects())
	{

		const std::optional<intersection> intersection = obj->intersects(outgoing);
		if (intersection.has_value() && intersection.value().hits && intersection.value().tmin<distance){
			return true;
		}
		
	}
	return false;

}

