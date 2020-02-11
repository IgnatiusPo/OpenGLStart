#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include <GL/glew.h>
VertexArray::VertexArray()
{
	//GLCall(glGenVertexArrays(1, &_RendererID));
}


//VertexArray::VertexArray(VertexArray&& vArray)
//{
//	_RendererID = vArray._RendererID;
//	vArray._RendererID = 0;
//}

//VertexArray::VertexArray(const VertexArray& vArray)
//{
//	_RendererID = vArray._RendererID;
//}

VertexArray::~VertexArray()
{
	//GLCall(glDeleteVertexArrays(1, &_RendererID));
}

//void VertexArray::Init()
//{
//	GLCall(glGenVertexArrays(1, &_RendererID));
//}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	if (_RendererID == 0)
		GLCall(glGenVertexArrays(1, &_RendererID));

	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element._normalized, layout.GetStride(),(const void*) offset));
		offset += element.count * GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
