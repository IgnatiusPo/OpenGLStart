#include "RenderObject.h"
#include "StlData.h"
#include "VertexBufferLayout.h"
RenderObject::RenderObject(StlData* object) : _object(object)
{
	//get dir of this shit fucking moron
	VertexArray vaObject;
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	_fullSize = _object->GetFullVerticesSize();
	unsigned int realSize;
	void* verticies = _object->GetPositionsAndNormals(realSize);
	_vBuffer.BindData(verticies, _fullSize * sizeof(StlData::Vertex));
	_vArray.AddBuffer(_vBuffer, layout);
}


RenderObject::~RenderObject()
{
}

void RenderObject::UseShader(Shader* shader)
{
	_shader = shader;
}

void RenderObject::Draw()
{
	if (_lastRenderSize < _fullSize) {
		unsigned int realSize;
		void* verticies = _object->GetPositionsAndNormals(realSize);
		_vBuffer.AddSubData(_lastRenderSize * sizeof(StlData::Vertex), (realSize - _lastRenderSize) * sizeof(StlData::Vertex), (char*)verticies + (_lastRenderSize * sizeof(StlData::Vertex)));
		_lastRenderSize = realSize;
	}

	_vArray.Bind();
	glDrawArrays(GL_TRIANGLES, 0, _lastRenderSize);
}
