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
	std::vector<Material> Materials;
	std::vector<Shader> Shaders;
	std::map<MaterialFeatureMask, ShaderID> MaterialFeatureToShader;
 

	void Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Init()
	{
		// init vertex arrays for quad and cube
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

	void DrawShadowPass(const Scene& scene, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& WS_ViewPosition, const glm::vec3& dirLightDirection)
	{
		for (auto& model : scene._sceneObjects)
		{
			//use unite shader
			for (auto& mesh : model._meshes)
			{
				Shader* CurrentShader = nullptr;

				MaterialProperties props = GetMaterialByID(mesh.GetMaterial())->properties;
				props._mask |= eShadowPass;
				CurrentShader = GetShaderByID(GetShaderIDFromMaterialProps(props));

				CurrentShader->Bind();
				CurrentShader->SetUniform("u_Model", mesh._modelMat);
				CurrentShader->SetUniform("u_Projection", projection);
				CurrentShader->SetUniform("u_View", view);
				//CurrentShader->SetUniform("u_ViewPosition", WS_ViewPosition);
				//CurrentShader->SetUniform("u_DirLight.direction", dirLightDirection);

				ApplyMaterial(mesh.GetMaterial(), CurrentShader);

				DrawInternal(mesh.GetVA(), 0, mesh.GetVB().GetCount());
			}
		}
	}

	void Draw(const Scene& scene, const glm::mat4& view,const glm::mat4& projection, const glm::vec3& WS_ViewPosition, const glm::vec3& dirLightDirection, const glm::mat4 lightView, const glm::mat4 lightProj)
	{
		for (auto& model : scene._sceneObjects)
		{
			//use unite shader
			for (auto& mesh : model._meshes)
			{
				Shader* CurrentShader = nullptr;

				const MaterialProperties & props = GetMaterialByID(mesh.GetMaterial())->properties;
				CurrentShader = GetShaderByID(GetShaderIDFromMaterialProps(props));
				
				CurrentShader->Bind();
				CurrentShader->SetUniform("u_Model", mesh._modelMat);
				CurrentShader->SetUniform("u_Projection", projection);
				CurrentShader->SetUniform("u_View", view);
				CurrentShader->SetUniform("u_ViewPosition", WS_ViewPosition);
				CurrentShader->SetUniform("u_DirLight.direction", dirLightDirection);
				CurrentShader->SetUniform("u_LightView", lightView);
				CurrentShader->SetUniform("u_LightProjection", lightProj);
				//todo maybe use here shared_ptr, as i do EVERYWHERE?
				ApplyMaterial(mesh.GetMaterial(), CurrentShader);

				//object.GetVB().Bind();
				DrawInternal(mesh.GetVA(), 0, mesh.GetVB().GetCount());
			}
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

	void DrawCube(glm::mat4 modelMat, glm::mat4 projectionMat, glm::mat4 viewMat, Shader* shader)
	{
		shader->Bind();
		shader->SetUniform("u_Model", modelMat);
		shader->SetUniform("u_Projection", projectionMat);
		shader->SetUniform("u_View", viewMat);

		CubeVA.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, CubeVB.GetCount()));
	}

	void DrawCube(glm::mat4 projectionMat, glm::mat4 viewMat, Shader* shader)
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
		if (ID >= Renderer::Textures.size() || ID == Texture::InvalidTextureID)
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

	Material* GetMaterialByID(MaterialID ID)
	{
		if (ID >= Renderer::Materials.size() || ID == Material::InvalidMaterialID)
		{
			ASSERT(false);
			return nullptr;
		}
		return &Renderer::Materials[ID];
	}
	Shader* GetShaderByID(ShaderID ID)
	{
		if (ID >= Renderer::Shaders.size() || ID == Shader::InvalidShaderID)
		{
			ASSERT(false);
			return nullptr;
		}
		return &Renderer::Shaders[ID];

	}

	MaterialID CreateDefaultPhongMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const float& shininess)
	{
		MaterialID NewID = (MaterialID)Renderer::Materials.size();
		Renderer::Materials.emplace_back();
		Material& NewMaterial = Renderer::Materials[NewID];

		NewMaterial.properties._mask |= MaterialFeatures::eDefaultPhongModel;
		NewMaterial.properties._mask |= MaterialFeatures::eHasNormal;

		Uniform uAmbient;
		uAmbient.name = "material.ambient";
		uAmbient.type = UniformType::vec3f;
		uAmbient.v3 = ambient;
		NewMaterial.uniforms.push_back(uAmbient);

		Uniform uDiffuse;
		uDiffuse.name = "material.diffuse";
		uDiffuse.type = UniformType::vec3f;
		uDiffuse.v3 = diffuse;
		NewMaterial.uniforms.push_back(uDiffuse);


		Uniform uSpecular;
		uSpecular.name = "material.specular";
		uSpecular.type = UniformType::vec3f;
		uSpecular.v3 = specular;
		NewMaterial.uniforms.push_back(uSpecular);

		Uniform uShininess;
		uShininess.name = "material.shininess";
		uShininess.type = UniformType::vec1f;
		uShininess.v1 = glm::vec1(shininess);
		NewMaterial.uniforms.push_back(uShininess);

		return NewID;
	}

	MaterialID CreateNewMaterial()
	{
		MaterialID NewID = (MaterialID)Renderer::Materials.size();
		Renderer::Materials.emplace_back();
		return NewID;
	}
	
	ShaderID GetShaderIDFromMaterialProps(const MaterialProperties& props)
	{
		auto shaderIt = MaterialFeatureToShader.find(props._mask);
		if (shaderIt != MaterialFeatureToShader.end())
		{
			return shaderIt->second;
		}

		ShaderID NewID = (ShaderID)Renderer::Shaders.size();
		std::string version = SHADER_VERSION;
		std::string vertexShader = version + '\n';
		std::string fragmentShader = version + '\n';
		//todo
		//std::string additionalInfo;
		//if ( props._mask & MaterialFeatures::eDefaultPhongModel )
		//{
		//	if (props._mask & MaterialFeatures::eHasNormal)
		//	{
		//		if ( props._mask & MaterialFeatures::eHasUV )
		//		{
		//			vertexShader = vertexShader + "#define HAS_TEXCOORD 1" + '\n';
		//			fragmentShader = fragmentShader + "#define HAS_TEXCOORD 1" + '\n';
		//		}
		//		vertexShader += Shader::ParseShader("res/shaders/BasicVert.shader");
		//		fragmentShader += Shader::ParseShader("res/shaders/PhongFrag.shader");
		//		Renderer::Shaders.emplace_back(vertexShader, fragmentShader);
		//	}
		//}
		//else
		//{

		if (props._mask & MaterialFeatures::eShadowPass)
		{
			vertexShader = vertexShader + "#define SHADOW_PASS 1" + '\n';
			fragmentShader = fragmentShader + "#define SHADOW_PASS 1" + '\n';
		}
		
		if (props._mask & MaterialFeatures::eHasNormal)
		{
			if (props._mask & MaterialFeatures::eHasUV)
			{
				vertexShader = vertexShader + "#define HAS_TEXCOORD 1" + '\n';
				fragmentShader = fragmentShader + "#define HAS_TEXCOORD 1" + '\n';

				if (props._mask & MaterialFeatures::eHasDiffuseTexture)
				{
					fragmentShader = fragmentShader + "#define HAS_DIFFUSE_TEXTURE 1" + '\n';
				}
			}
			vertexShader += Shader::ParseShader("res/shaders/BasicVert.shader");
			fragmentShader += Shader::ParseShader("res/shaders/PhongFrag.shader");
			Renderer::Shaders.emplace_back(vertexShader, fragmentShader);
		}
		else
		{
			ASSERT(false);
			return Shader::InvalidShaderID;
		}


		//}

		MaterialFeatureToShader.insert({ props._mask, NewID });
		return NewID;
	}
	ShaderID CreateShaderFromPath(const char* vertPath, const char* fragmentPath)
	{
		std::string version = SHADER_VERSION;
		std::string vertexShader = version + '\n';
		std::string fragmentShader = version + '\n';
		vertexShader += Shader::ParseShader(vertPath);
		fragmentShader += Shader::ParseShader(fragmentPath);

		ShaderID NewID = (ShaderID)Renderer::Shaders.size();
		Renderer::Shaders.emplace_back(vertexShader, fragmentShader);
		return NewID;
	}

	void ApplyMaterial(const MaterialID& MatID, Shader* shader)
	{
		if (MatID >= Renderer::Materials.size() || MatID == Material::InvalidMaterialID)
		{
			ASSERT(false);
			return;
		}
		const Material& Mat = Renderer::Materials[MatID];
		for (const auto& uniform : Mat.uniforms)
		{
			shader->SetUniform(uniform);
		}
	}

}
