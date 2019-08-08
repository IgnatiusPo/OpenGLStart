#include "Renderer.h"

#include <iostream>


GlobalShaderState GShaderState = GlobalShaderState::NORMAL;
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw_Internal(VertexArray& va, unsigned int first, unsigned int count)
{
	GLCall(glDrawArrays(GL_TRIANGLES, first, count));
}
void Renderer::Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) 
{
	//shader.Bind();
	//va.Bind();
	//ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::BindAndDraw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) 
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(VertexArray& va, const Shader& shader, unsigned int first, unsigned int count )
{
	//switch (GShaderState)
	//{
	//case GlobalShaderState::NORMAL:
	//	Renderer::Draw_Internal(va, first, count); // just draw using normal settings
	//	break;
	//case GlobalShaderState::DEPTH_ONLY:
	//{
	//	const Shader* OnlyDepth = Shader::GetDepthOnlyShader();
	//	OnlyDepth->Bind();
	//	Renderer::Draw_Internal(va, first, count);
	//	shader.Bind();
	//	break;
	//}
	//default:
	//	assert(false); // GShaderState is not initialized!
	//	break;
	//}
	Renderer::Draw_Internal(va, first, count);
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
