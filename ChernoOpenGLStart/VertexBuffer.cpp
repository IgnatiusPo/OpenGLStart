#include "VertexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data,const unsigned int& size, unsigned int count) : _count(count)
{
	GLCall(glGenBuffers(1, &_RendererID));
	BindData(data, size, count);
}

VertexBuffer::VertexBuffer()
{
	//GLCall(glGenBuffers(1, &_RendererID));
}

VertexBuffer::~VertexBuffer()
{
	//GLCall(glDeleteBuffers(1, &_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _RendererID)); 
}

void VertexBuffer::Unbind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::AddSubData(const unsigned int& offset,const unsigned int& size, const void* data) const
{
	GLCall(glNamedBufferSubData(_RendererID, offset, size, data));
}

void VertexBuffer::BindData(const void* data,const unsigned int& size, unsigned int count)
{
	if (_RendererID == 0)
		GLCall(glGenBuffers(1, &_RendererID));

	_count = count;
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Init(const void* data, const unsigned int& size, unsigned int count)
{
	GLCall(glGenBuffers(1, &_RendererID));
	BindData(data, size, count);
}
