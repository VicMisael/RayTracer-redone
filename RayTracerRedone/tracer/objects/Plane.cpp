#include "Plane.h"
#include <glm/geometric.hpp>
#include "../utils/utility.h"
#include "../utils/OrthonormalBase.h"


glm::vec3 computeU(glm::vec3 normal) {
	glm::vec3 tangent = glm::vec3(1, 0, 0);
	if (glm::dot(normal, tangent) > 0.99) // they are too parallel
		tangent = glm::vec3(0, 1, 0);

	return glm::normalize(glm::cross(normal, tangent));
}

glm::vec3 computeV(const glm::vec3& normal, const glm::vec3& u) {
	return glm::cross(normal, u);
}

std::tuple<float, float> computeUV(const glm::vec3& pointInPlane, const glm::vec3& otherPoint, const glm::vec3& normal) {
	glm::vec3 u = computeU(normal);
	glm::vec3 v = computeV(normal, u);

	glm::vec3 delta = otherPoint - pointInPlane;

	float uCoordinate = glm::dot(delta, u);
	float vCoordinate = glm::dot(delta, v);

	return { glm::mod(uCoordinate / 100.0f,1.0f), glm::mod(vCoordinate / 100.0f,1.0f) };
}

Vec3_SoA computeU_SoA(const Vector3_SoA& normal) {
	Vec3_SoA tangent1(1, 0, 0);
	Vec3_SoA tangent2(0, 1, 0);
	const auto dot_batch = utility::dot_SoA(tangent1, normal);
	const auto mask = dot_batch > 0.99;


	const auto x = xs::select(mask, tangent1.x, tangent2.x);
	const auto y = xs::select(mask, tangent1.y, tangent2.y);
	const auto z = xs::select(mask, tangent1.z, tangent2.z);
	Vec3_SoA selected(x, y, z);
	return utility::normalize_SoA(utility::cross_SoA(normal, selected));

}

Vec3_SoA computeV_SoA(const Vec3_SoA& normal, const Vec3_SoA& u) {
	return utility::cross_SoA(normal, u);
}

std::tuple<batch_type, batch_type> computeUV_SoA(const Vector3_SoA& pointsInPlane, const Vector3_SoA& otherPoint, const Vector3_SoA& normal) {
	const auto u = computeU_SoA(normal);
	const auto v = computeV_SoA(normal, u);
	const Vector3_SoA delta = {
		pointsInPlane.x - otherPoint.x,
		pointsInPlane.y - otherPoint.y,
		pointsInPlane.z - otherPoint.z,
	};

	auto uCoord = utility::dot_SoA(delta, u);
	auto vCoord = utility::dot_SoA(delta, v);

	return { xs::fmod(uCoord / 100.0f, batch_type(1.0f)),  xs::fmod(vCoord / 100.0f, batch_type(1.0f)) };
}



std::optional<intersectionRec> Plane::intersects(const Ray& ray) const {
	using namespace glm;
	const float dot_dir_normal = dot(ray.direction, normal);
	const float t = dot(point - ray.origin, normal) / dot_dir_normal;
	if (t > Constants::EPSILON) {
		const auto intersectionPoint = ray.point_at(t);
		const auto [u, v] = computeUV(point, intersectionPoint, normal);
		return intersectionRec{ t, ray.point_at(t), normal, material, u, v };
	}

	return {};
}
intersectionRecSoA Plane::intersects(const RaySoA& ray) const {
	const auto& direction = ray.direction;
	const auto& origin = ray.origin;
	const auto& normal = utility::fromVec3(this->normal);
	const auto dot_dir_normal = utility::dot_SoA(direction, utility::fromVec3(this->normal));
	const auto point = utility::fromVec3(this->point);

	const auto point_minus_origin = Vector3_SoA{
		point.x - origin.x,
		point.y - origin.y,
		point.z - origin.z,
	};
	const auto t = utility::dot_SoA(point_minus_origin, normal) / dot_dir_normal;
	const auto mask = t > batch_type(Constants::EPSILON);

	if (xs::none(mask)) {
		return { mask };
	}

	const auto intersectionPoint = ray.point_at(t);
	const auto [u, v] = computeUV_SoA(point, intersectionPoint, normal);

	intersectionRecSoA rec;
	rec.normal = normal;
	rec.hit_point = intersectionPoint;
	rec.tmin = t;
	rec.u = u;
	rec.v = v;
	rec.intersects = mask;
	for (size_t i = 0; i < SIMD_WIDTH; ++i) {
		rec.materials[i] = this->material;
	}

	return rec;
}

void Plane::transform(Matrix4x4 m) {
	point = Vector3(m * Vector4(point, 1));
	normal = Vector3(m * Vector4(normal, 0));
}

float Plane::getArea() const {
	return INFINITY;
}

std::tuple<Point3, Vector3> Plane::pointAtSurface() const {
	const OrthonormalBase uvw(this->normal);
	return { this->point + utility::random(FLT_MIN, FLT_MAX) * (uvw.u() + uvw.v()), normal };

}
