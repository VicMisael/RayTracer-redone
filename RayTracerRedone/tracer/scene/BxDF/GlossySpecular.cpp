#include "GlossySpecular.h"
#include "../../utils/utility.h"
#include <glm/geometric.hpp>

ColorVec GlossySpecular::rho(const Vector3& wo) const
{
	return { 0,0,0 };
}

ColorVec GlossySpecular::f(const intersection& intersection, const Vector3& wo, const Vector3& wi) const
{
	ColorVec L;
	const Vector3 &normal = intersection.normal;
	const float n_dot_wi = dot(normal , wi);
	const Vector3 r = -wi + 2.0f * normal * n_dot_wi;
	float r_dot_two = dot(normalize(r), normalize(wo));
	if (r_dot_two > 0.0){
		
		L = color_ * ks_ * pow(r_dot_two, exp_);
	}
	return L;
}

sample_f_out GlossySpecular::sample_f(const intersection& intersection, const Vector3& wo) const
{
	const Vector3& normal = intersection.normal;
	const float n_dot_two = dot(normal, wo);
	const Vector3 r = -wo + 2.0f * normal * n_dot_two;

	const auto w = r;
	const auto u = normalize(cross(Vector3(0.00424, 1, 0.00764),w));
	const auto v = cross(u, w);

	//TODO: Improve sampling
	const auto wi = utility::random_in_hemisphere(normal);


	const float phong_lobe = pow(dot(r , wi), exp_);
	const float pdf = phong_lobe * (dot(normal , wi));

	return { ks_ * color_ * phong_lobe,wi,pdf };
}
