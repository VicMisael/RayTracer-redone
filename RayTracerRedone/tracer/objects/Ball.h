#pragma once
#include "VirtualObject.h"
class Ball: public VirtualObject
{
public:
	Point3 center;
	float radius;
	Ball(Point3 _center, float _radius, std::shared_ptr<Material> _material) :VirtualObject(_material), center(_center), radius(_radius) {};
	std::optional<intersection> intersects(const Ray &ray) const override;

    std::optional<std::shared_ptr<AABB>> bounding_box() const override;

    void transform(Matrix4x4 m) override;

};

