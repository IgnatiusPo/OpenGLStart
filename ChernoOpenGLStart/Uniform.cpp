#include "Uniform.h"
void CreateNameForTextureUniform(Uniform& uniform)
{
	assert(uniform.type == UniformType::tex);
	switch (uniform.tex.textureClass)
	{
	case TextureClass::shadowmap:
	{
		uniform.name = "shadowMap";
		break;
	}
	case TextureClass::albedo:
	{
		uniform.name = "texDiffuse";
		break;
	}
	case TextureClass::specular:
	{
		uniform.name = "texSpecular";
		break;
	}
	}
}
