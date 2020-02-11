#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;
class VertexArray
{
private:
	unsigned int _RendererID = 0;
public:
	VertexArray();
	//VertexArray(VertexArray&& vArray);
	//VertexArray(const VertexArray& vArray) = delete;
	~VertexArray();

	//void Init();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};

