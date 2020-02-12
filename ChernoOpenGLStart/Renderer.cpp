#include "Renderer.h"
#include "Shader.h"
#include <GL/glew.h>
#include "VertexBufferLayout.h"
#include "VertexArray.h"

#include "Macroses.h"
//#include <iostream>
//
//
//GlobalShaderState GShaderState = GlobalShaderState::NORMAL;
//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//}
//
//bool GLLogError(const char* function, const char* file, int line)
//{
//	while (GLenum error = glGetError())
//	{
//		std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
//		return false;
//	}
//	return true;
//}

//void Renderer::Draw_Internal(VertexArray& va, unsigned int first, unsigned int count)
//{
//	GLCall(glDrawArrays(GL_TRIANGLES, first, count));
//}
//void Renderer::Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) 
//{
//	//shader.Bind();
//	//va.Bind();
//	//ib.Bind();
//	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
//
//}
//
//void Renderer::BindAndDraw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) 
//{
//	shader.Bind();
//	va.Bind();
//	ib.Bind();
//	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
//}
//
//void Renderer::Draw(VertexArray& va, const Shader& shader, unsigned int first, unsigned int count )
//{
//	//switch (GShaderState)
//	//{
//	//case GlobalShaderState::NORMAL:
//	//	Renderer::Draw_Internal(va, first, count); // just draw using normal settings
//	//	break;
//	//case GlobalShaderState::DEPTH_ONLY:
//	//{
//	//	const Shader* OnlyDepth = Shader::GetDepthOnlyShader();
//	//	OnlyDepth->Bind();
//	//	Renderer::Draw_Internal(va, first, count);
//	//	shader.Bind();
//	//	break;
//	//}
//	//default:
//	//	assert(false); // GShaderState is not initialized!
//	//	break;
//	//}
//	Renderer::Draw_Internal(va, first, count);
//}
//

namespace Renderer
{

	std::vector<Texture> Textures;
	std::vector<Cubemap> CubemapTextures;

 

	void Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Init()
	{
		VertexBufferLayout QuadLayout;
		QuadLayout.Push<float>(2);
		QuadVB.Init(QuadPositions, sizeof(QuadPositions), (sizeof(QuadPositions) / sizeof(float)) / 2);
		//QuadVB.BindData(QuadPositions, sizeof(QuadPositions), 4);
		QuadVA.AddBuffer(QuadVB, QuadLayout);

		VertexBufferLayout CubeLayout;
		CubeLayout.Push<float>(3);
		CubeVB.Init(CubePositions, sizeof(CubePositions), (sizeof(CubePositions) / sizeof(float)) / 3);
		CubeVA.AddBuffer(CubeVB, CubeLayout);

	}

	void Draw(const Scene& scene, const glm::mat4& view,const glm::mat4& projection, const glm::vec3& WS_ViewPosition)
	{
		for (auto& object : scene._sceneObjects)
		{
			std::shared_ptr<Shader> _currentShader = object._shader;
			_currentShader->Bind();
			_currentShader->SetUniform("u_Model", object._modelMat);
			_currentShader->SetUniform("u_Projection", projection);
			_currentShader->SetUniform("u_View", view);
			_currentShader->SetUniform("u_ViewPosition", WS_ViewPosition);

			//object.GetVB().Bind();
			DrawInternal(object.GetVA(), 0, object.GetVB().GetCount());
		}
	}

	void DrawInternal(const VertexArray& va, unsigned int first, unsigned int count)
	{
		va.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, first, count));
	}

	void DrawQuadFS()
	{
		QuadVA.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, QuadVB.GetCount()));
	}

	void DrawCube(glm::mat4 modelMat, glm::mat4 projectionMat, glm::mat4 viewMat, std::shared_ptr<Shader> shader)
	{
		shader->Bind();
		shader->SetUniform("u_Model", modelMat);
		shader->SetUniform("u_Projection", projectionMat);
		shader->SetUniform("u_View", viewMat);

		CubeVA.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, CubeVB.GetCount()));
	}

	void DrawCube(glm::mat4 projectionMat, glm::mat4 viewMat, std::shared_ptr<Shader> shader)
	{
		shader->Bind();
		shader->SetUniform("u_Projection", projectionMat);
		shader->SetUniform("u_View", viewMat);

		CubeVA.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, CubeVB.GetCount()));
	}

	TextureID CreateTexture(const std::string& path)
	{
		TextureID NewID = (TextureID)Renderer::Textures.size();
		Renderer::Textures.emplace_back(path);
		return NewID;
	}

	TextureID CreateCubemapTexture(std::vector<std::string> faces)
	{
		TextureID NewID = (TextureID)Renderer::CubemapTextures.size();
		Renderer::CubemapTextures.emplace_back(faces);
		return NewID;
	}

	Texture* GetTextureByID(TextureID ID)
	{
		if (ID >= Renderer::Textures.size() || Texture::InvalidTextureID)
		{
			ASSERT(false);
			return nullptr;
		}
		return &Renderer::Textures[ID];
	}

	Cubemap* GetCubemapTextureByID(TextureID ID)
	{
		if (ID >= Renderer::CubemapTextures.size() || ID == Texture::InvalidTextureID)
		{
			ASSERT(false);
			return nullptr;
		}
		return &Renderer::CubemapTextures[ID];
	}

}
