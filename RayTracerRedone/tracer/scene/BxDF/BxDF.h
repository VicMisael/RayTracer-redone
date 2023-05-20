#pragma once
#include <vector>

#include "../../utils/ColorVec.h"
#include "../../utils/Intersection.h"
struct sample_f{
	ColorVec color;
	Vector3 wi;
};

class BxDF
{

public:
	//Based of Physically based rendering
	/*
	 *The hemispherical-hemispherical reflectance of a surface, denoted by phh, is a spectral
		value that gives the fraction of incident light reflected by a surface when the incident
		light is the same from all directions. It is
	 */
	virtual ColorVec rho(const Vector3& wo) = 0;
	virtual ColorVec f(const intersection &intersection,const Vector3 &wo,const Vector3 &wi) = 0;
	virtual sample_f sample_f(const intersection& intersection,const Vector3 &wo);
};

