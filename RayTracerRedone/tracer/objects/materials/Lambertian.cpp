#include "Lambertian.h"
#include "../../utils/utility.h"
std::optional<scatter_out> Lambertian::scatter(scatter_in in)
{
	const auto normal= in.intersection_data.intersection->normal;
	auto out_dir = normal+utility::random(-1,1)
}
