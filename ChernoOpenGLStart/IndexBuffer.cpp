#include "IndexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : _Count(count)
{
	GLCall(glGenBuffers(1, &_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}
