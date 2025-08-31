#pragma once
#include "../utils/Types.h"
class Ray
{
public:
	Point3 origin;
	Vector3 direction;
	Ray() :origin(0), direction(0) {}
	Ray(Point3 _origin, Vector3 _direction) :origin(_origin), direction(_direction) {};

	const Point3 point_at(float t) const;
};


struct RaySoA {
	Point3_SoA origin;
	Vector3_SoA direction;

	RaySoA() = default;
	RaySoA(Point3_SoA o, Vector3_SoA d) : origin(o), direction(d) {}

	// Pack SIMD_WIDTH scalar Rays into one SoA Ray
	RaySoA(const std::array<Ray, SIMD_WIDTH>& rays) {
		pack(rays.data(), SIMD_WIDTH);
	}

	// Pack up to SIMD_WIDTH rays from a pointer
	RaySoA(const Ray* rays, size_t count) {
		pack(rays, count);
	}

	// Helper function to pack rays
	void pack(const Ray* rays, size_t count) {
		float ox[SIMD_WIDTH], oy[SIMD_WIDTH], oz[SIMD_WIDTH];
		float dx[SIMD_WIDTH], dy[SIMD_WIDTH], dz[SIMD_WIDTH];

		for (size_t i = 0; i < SIMD_WIDTH; i++) {
			if (i < count) {
				ox[i] = rays[i].origin.x;
				oy[i] = rays[i].origin.y;
				oz[i] = rays[i].origin.z;

				dx[i] = rays[i].direction.x;
				dy[i] = rays[i].direction.y;
				dz[i] = rays[i].direction.z;
			}
			else {
				// Fallback: repeat the last valid ray
				ox[i] = rays[count - 1].origin.x;
				oy[i] = rays[count - 1].origin.y;
				oz[i] = rays[count - 1].origin.z;

				dx[i] = rays[count - 1].direction.x;
				dy[i] = rays[count - 1].direction.y;
				dz[i] = rays[count - 1].direction.z;
			}
		}

		origin.x = batch_type::load_unaligned(ox);
		origin.y = batch_type::load_unaligned(oy);
		origin.z = batch_type::load_unaligned(oz);

		direction.x = batch_type::load_unaligned(dx);
		direction.y = batch_type::load_unaligned(dy);
		direction.z = batch_type::load_unaligned(dz);
	}

	// Extract scalar ray back from one SIMD lane
	Ray get_lane(size_t i) const {
		return Ray(
			{ origin.x.get(i), origin.y.get(i), origin.z.get(i) },
			{ direction.x.get(i), direction.y.get(i), direction.z.get(i) }
		);
	}

	// Compute point_at(t) in SoA form
	Point3_SoA point_at(const batch_type& t) const {
		return Point3_SoA{
			origin.x + direction.x * t,
			origin.y + direction.y * t,
			origin.z + direction.z * t
		};
	}
};