#pragma once
#include "Uniform.h"
#include <vector>


typedef int MaterialID;
struct Material
{
	std::vector<Uniform> uniforms;


	const static MaterialID InvalidMaterialID = -1;
};

