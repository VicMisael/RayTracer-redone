#include "Plane.h"
#include <glm/geometric.hpp>


vec3 computePrimaryTexDir(vec3 normal)
{

    vec3 a = cross(normal, vec3(1, 0, 0));
    vec3 b = cross(normal, vec3(0, 1, 0));

    vec3 max_ab = dot(a, a) < dot(b, b) ? b : a;

    vec3 c = cross(normal, vec3(0, 0, 1));

    return normalize(dot(max_ab, max_ab) < dot(c, c) ? c : max_ab);
}

std::tuple<float,float> get_plane_uv(const Vector3 normal,const Point3 point_in_plane,const Point3 point){
    glm::vec3 U_direction = glm::normalize(glm::cross(normal, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (glm::length(U_direction) < 0.001f)
        U_direction = glm::normalize(glm::cross(normal, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::vec3 V_direction = glm::normalize(glm::cross(normal,U_direction));

    glm::vec3 W = point;
    
    float u = glm::dot(W, U_direction);
    float v = glm::dot(W, V_direction);

    return { u,v };
   }
std::optional<intersection> Plane::intersects(const Ray &ray) const
{
	using namespace glm;
	const float dot_dir_normal = dot(ray.direction, normal);
	const float t = dot(point - ray.origin, normal) / dot_dir_normal;
	if (t > Constants::EPSILON+0.001f) {
        const auto intersectionPoint=ray.point_at(t);
        const auto [u,v] = get_plane_uv(normal,point, intersectionPoint);
		return intersection{true,t,ray.point_at(t),normal,material.value(),u,v};
	}
	
	return {};
}
