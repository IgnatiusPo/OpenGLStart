#pragma once
#include <vector>
#include <string>
class Cubemap
{
	unsigned int _RendererID = 0;
public:
	Cubemap();
	Cubemap(std::vector<std::string> faces);
	~Cubemap();
	
	void Init(std::vector<std::string> faces);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};

