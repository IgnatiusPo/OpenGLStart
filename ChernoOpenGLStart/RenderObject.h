//#pragma once
//#include "Renderer.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//class StlData;
//
//extern GlobalShaderState GShaderState;
//
//class RenderObject
//{
//	StlData* _object;
//	VertexArray _vArray;
//	VertexBuffer _vBuffer;
//	unsigned int _fullSize;
//	unsigned int _lastRenderSize;
//
//	//for later use
//	glm::mat4 _modelMat;
//public:
//	/* because of using StlData::GetFullVerticesSize it would be blocking function. See StlData::GetFullVerticesSize() */
//	Shader* _shader;
//	RenderObject(StlData* object);
//	~RenderObject();
//
//	void UseShader(Shader* shader);
//	void Draw();
//
//	void SetModelMatrix(glm::mat4 modelMatrix);
//private:
//};
//
