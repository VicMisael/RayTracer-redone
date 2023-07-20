#include "equidistant_point_sampler.h"
#include <cmath>

double halton(int index, int base) {
    double result = 0;
    double f = 1.0 / base;
    int i = index;
    while(i > 0) {
        result = result + f * (i % base);
        i = i / base;
        f = f / base;
    }
    return result;
}

std::vector<std::tuple<float, float>> equidistant_point_sampler::generate_points()
{
    std::vector<std::tuple<float, float>> points;
    points.reserve(num_samples);
    for (unsigned int i = 1; i <= num_samples; i++)
    {

        points.emplace_back(halton(i,2), halton(i,3));
    }
	return points;
}
