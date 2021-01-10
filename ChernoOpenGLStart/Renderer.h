#pragma once
//#include <GL/glew.h>
#include "Scene.h"
#include <iostream>
#include "Texture.h"
#include "Cubemap.h"
#include "Material.h"
#include <vector>
#include <map>


//#define ASSERT(x) if(!(x)) __debugbreak();
//
//#define GLCall(x) GLClearError();\
//	x;\
//	ASSERT(GLLogError(#x, __FILE__, __LINE__))
//
//void GLClearError();
//bool GLLogError(const char* function, const char* file, int line);
//
//
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
class Shader;
namespace Renderer
{
	static const char* SHADER_VERSION = "#version 330 core";


	//class Shader* _currentShader;
	void Init();
	//todo global uniform buffer for lightDir
	void DrawShadowPass(const Scene& scene, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& WS_ViewPosition, const glm::vec3& dirLightDirection);
	void Draw(const Scene& scene, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& WS_ViewPosition, const glm::vec3& dirLightDirection, const glm::mat4 lightView, const glm::mat4 lightProj);
	void Clear();
	void DrawInternal(const VertexArray& va, unsigned int first, unsigned int count);
	void DrawQuadFS();
	void DrawCube(glm::mat4 modelMat, glm::mat4 projectionMat, glm::mat4 viewMat, Shader* shader);
	void DrawCube(glm::mat4 projectionMat, glm::mat4 viewMat, Shader* shader);

	TextureID CreateTexture(const std::string& path);
	TextureID CreateCubemapTexture(std::vector<std::string> faces);
	Texture* GetTextureByID(TextureID ID);
	Cubemap* GetCubemapTextureByID(TextureID ID);
	Material* GetMaterialByID(MaterialID ID);
	Shader* GetShaderByID(ShaderID ID);
	ShaderID GetShaderIDFromMaterialProps(const MaterialProperties& props);

	MaterialID CreateDefaultPhongMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const float& shininess);
	MaterialID CreateNewMaterial();
	//ShaderID CreateShaderFromMaterialProperties(const MaterialProperties& props);
	ShaderID CreateShaderFromPath(const char* vertPath, const char* fragmentPath);
	void ApplyMaterial(const MaterialID& MatID, Shader* shader);

	static const float QuadPositions[] = { //vertex attributes for a quad that fills the entire screen in NDC.
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f,

		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};
	 
	static const float CubePositions[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	static VertexArray QuadVA;
	static VertexBuffer QuadVB;
	
	static VertexArray CubeVA;
	static VertexBuffer CubeVB;


	extern std::vector<Texture> Textures;
	extern std::vector<Cubemap> CubemapTextures;
	extern std::vector<Material> Materials;
	extern std::vector<Shader> Shaders;
	extern std::map<MaterialFeatureMask, ShaderID> MaterialFeatureToShader;
};