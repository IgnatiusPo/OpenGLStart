#pragma once
#include "Renderer.h"

class StlData;
class RenderObject
{
	StlData* _object;
	VertexArray _vArray;
	VertexBuffer _vBuffer;
	unsigned int _fullSize;
	unsigned int _lastRenderSize;
public:
	/* because of using StlData::GetFullVerticesSize it would be blocking function. See StlData::GetFullVerticesSize() */
	Shader* _shader;
	RenderObject(StlData* object);
	~RenderObject();

	void UseShader(Shader* shader);
	void Draw();
};

