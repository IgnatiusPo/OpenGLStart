#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int _RendererID;
	std::string	 _Filepath;
	unsigned char* _LocalBuffer;
	int _Width, _Height, _BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return _Width; }
	inline int GetHeight() const { return _Height; }

};