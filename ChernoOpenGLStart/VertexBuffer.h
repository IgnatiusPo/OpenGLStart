#pragma once

class VertexBuffer
{
private:
	unsigned int _RendererID = 0; 
	unsigned int _count;
public:
	VertexBuffer();
	VertexBuffer(const void* data, const unsigned int& size, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void AddSubData(const unsigned int& offset, const unsigned int& size, const void* data) const;
	void BindData(const void* data, const unsigned int& size, unsigned int count);
	void Init(const void* data, const unsigned int& size, const unsigned int& count);
	unsigned int GetCount() const
	{
		return _count;
	}
};