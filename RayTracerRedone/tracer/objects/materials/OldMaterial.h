#pragma once
#include "Material.h"
//Simple material based off of My old implementation
class OldMaterial :
    public Material
{
public:
    OldMaterial(float specular, float reflectiveness,ColorVec color): Material(color),specular_(specular), reflectiveness_(reflectiveness){};
	private:
    float specular_ = -1;
    float reflectiveness_ = -1;

};

