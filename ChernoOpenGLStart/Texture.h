#pragma once

#include "Renderer.h"
#include <string>
class Texture
{
protected:
	unsigned int _RendererID;
public:
	Texture();
	Texture(const std::string& path, int* Width, int* Height, int* channels);
	~Texture();

	virtual void Bind(unsigned int slot = 0) const;
	virtual void Unbind() const;

};