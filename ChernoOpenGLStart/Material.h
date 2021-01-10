#pragma once
#include "Uniform.h"
#include <vector>

typedef uint16_t MaterialFeatureMask;

enum  MaterialFeatures : MaterialFeatureMask
{
	eDefaultPhongModel = 1,
	eHasNormal = 1 << 1,
	eHasUV = 1 << 2,
	eHasDiffuseTexture = 1 << 3,
	eShadowPass = 1 << 4
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

