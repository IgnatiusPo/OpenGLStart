#pragma once
#include "Uniform.h"
#include <vector>

typedef uint16_t MaterialFeatureMask;

enum  MaterialFeatures : uint16_t
{
	eDefaultPhongModel = 1,
	eHasNormal = 1 << 1,
};
struct MaterialProperties
{
	MaterialFeatureMask _mask;
};

typedef int MaterialID;
struct Material
{
	std::vector<Uniform> uniforms;

	MaterialProperties properties;

	const static MaterialID InvalidMaterialID = -1;
};

