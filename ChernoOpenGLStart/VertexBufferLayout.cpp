#include "VertexBufferLayout.h"
#include <GL/glew.h>

unsigned int GetSizeOfType(unsigned int Type)
{
	switch (Type)
	{
	case GL_FLOAT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	//case GL_INT:
	//	return 4;
	case GL_UNSIGNED_BYTE:
		return 1;
	}
	ASSERT(false);
	return 0;
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
	_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	_Stride += count * GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	_Stride += count * GetSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const
{
	return _Elements;
}

unsigned int VertexBufferLayout::GetStride() const
{
	return _Stride;
}

