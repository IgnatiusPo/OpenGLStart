#pragma once
#include <vector>
#include "Renderer.h"
//#include <GL/glew.h>
unsigned int GetSizeOfType(unsigned int Type);

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char _normalized;
};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> _Elements;
	unsigned int _Stride;
public:
	VertexBufferLayout() : _Stride(0) {};

	template<typename T>
	void Push(unsigned int count);


	const std::vector<VertexBufferElement> GetElements() const ;
	unsigned int GetStride() const;
};

