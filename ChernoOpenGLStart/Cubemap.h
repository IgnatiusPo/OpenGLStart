#pragma once
#include "Texture.h"
class Cubemap : public Texture
{
public:
	Cubemap();
	Cubemap(std::vector<std::string> faces);
	~Cubemap();
	
	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;
};

