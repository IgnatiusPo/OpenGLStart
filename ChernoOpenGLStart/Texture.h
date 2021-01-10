#pragma once

//#include "Renderer.h"
#include <string>
#include "GL/glew.h"

typedef size_t TextureID;

enum class TextureType
{
	Texture_2D = GL_TEXTURE_2D,
	Texture_3D = GL_TEXTURE_3D
};

class Texture
{
	unsigned int _RendererID = -1;
public:
	//Texture();
	Texture(const std::string& path);

	void Init(const std::string& path);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	
public:
	int _width, _height, _nChannels = 0;

	const static TextureID InvalidTextureID = -1;
};