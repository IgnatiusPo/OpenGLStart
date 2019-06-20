#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path) : _RendererID(0), _Filepath(path), _LocalBuffer(nullptr), _Width(0), _Height(0), _BPP(0)
{

	stbi_set_flip_vertically_on_load(1);
	_LocalBuffer = stbi_load(path.c_str(), &_Width, &_Height, &_BPP, 4);

	GLCall(glGenTextures(1, &_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, _RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (_LocalBuffer)
		stbi_image_free(_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &_RendererID));
}

void Texture::Bind(unsigned int slot/*= 0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0	+ slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, _RendererID));

}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
