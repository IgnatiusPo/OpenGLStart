#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

enum class GlobalShaderState : uint8_t
{
	NORMAL,
	DEPTH_ONLY
};


#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);

class Renderer
{
private:
	static void Draw_Internal(VertexArray& va, unsigned int first, unsigned int count);
public:
	static void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	static void BindAndDraw(VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	static void Draw(VertexArray& va, const Shader& shader,unsigned int first, unsigned int count);
	void Clear() const;
};