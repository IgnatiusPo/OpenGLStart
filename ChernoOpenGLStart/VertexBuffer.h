#pragma once

class VertexBuffer
{
private:
	unsigned int _RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, const unsigned int& size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void AddSubData(const unsigned int& offset, const unsigned int& size, const void* data) const;
	void BindData(const void* data, const unsigned int& size);
};