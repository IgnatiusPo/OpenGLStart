#pragma once

#include "glm/glm.hpp"
#include <string>
#include "Texture.h"
enum class UniformType
{
	vec1f,
	vec2f,
	vec3f,
	vec4f,
	vec1i,
	vec2i,
	vec3i,
	vec4i,
	mat3,
	mat4,
	tex
};

enum class TextureClass : uint16_t
{
	shadowmap = 0,
	albedo,
	specular
};
struct TextureUniform
{
	TextureID textureID;
	TextureClass textureClass;
};
struct Uniform
{
	union {
		glm::vec1 v1;
		glm::vec2 v2;
		glm::vec3 v3;
		glm::vec4 v4;
		glm::ivec1 iv1;
		glm::ivec2 iv2;
		glm::ivec3 iv3;
		glm::ivec4 iv4;
		glm::mat3 m3;
		glm::mat4 m4;
		TextureUniform tex;
	};
	std::string name;
	UniformType type;
};

void CreateNameForTextureUniform(Uniform& uniform);

