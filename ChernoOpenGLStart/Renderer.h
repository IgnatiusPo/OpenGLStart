#pragma once
//#include <GL/glew.h>
#include "Scene.h"
#include <iostream>


#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);


//class Renderer
//{
//private:
//	static void Draw_Internal(VertexArray& va, unsigned int first, unsigned int count);
//public:
//	static void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader);
//	static void BindAndDraw(VertexArray& va, const IndexBuffer& ib, const Shader& shader);
//	static void Draw(VertexArray& va, const Shader& shader,unsigned int first, unsigned int count);
//	void Clear() const;
//};

namespace Renderer
{
	//class Shader* _currentShader;
	void Init();
	void Draw(const Scene& scene, glm::mat4 view, glm::mat4 projection, const glm::vec3& WS_ViewPosition);
	void Clear();
	void DrawInternal(const VertexArray& va, unsigned int first, unsigned int count);
	void DrawQuadFS();

	static const float QuadPositions[] = { //vertex attributes for a quad that fills the entire screen in NDC.
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f,

		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};

	static VertexArray QuadVA;
	static VertexBuffer QuadVB;


};