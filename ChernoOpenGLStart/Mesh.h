#pragma once
#include "VertexArray.h"
#include <string>
#include "glm/glm.hpp"
#include "Material.h"
#include <memory>
//todo need this for ShaderID
#include "Shader.h"
//#include "Model.h"
enum class ModelType
{
	STL,
	OBJ,
};

template<ModelType T>
struct Vertex
{
	glm::vec3 _position;
};

template<>
struct Vertex<ModelType::STL>
{
	glm::vec3 _position;
	glm::vec3 _normal;
	Vertex(glm::vec3 position, glm::vec3 normal) : _position(position), _normal(normal) {} ;
	Vertex() = default;
};

template<>
struct Vertex<ModelType::OBJ>
{
	glm::vec3 _position;
	glm::vec3 _normal;
	glm::vec2 _texCoord;
};

//class SubMesh
//{
//	VertexArray _vArray;
//	VertexBuffer _vBuffer;
//	void* _vertexData = nullptr;
//	MaterialID _material = Material::InvalidMaterialID;
//	const VertexArray& GetVA() const
//	{
//		return _vArray;
//	}
//	const VertexBuffer& GetVB() const
//	{
//		return _vBuffer;
//	}
//	void SetMaterial(const MaterialID& ID);
//	MaterialID GetMaterial() const
//	{
//		return _material;
//	}
//
//
//};

class Mesh
{
	VertexArray _vArray;
	VertexBuffer _vBuffer;
	//void* _vertexData = nullptr;
	ModelType _modelType;
	MaterialID _material = Material::InvalidMaterialID;
public:
	Mesh();
	Mesh( ModelType _modelType, VertexArray&& vArray, VertexBuffer&& vBuffer);
	~Mesh();
	//void UseShader(std::shared_ptr<class Shader> shader);
	void SetModelMatrix(glm::mat4 ModelMatrix);
	
	const VertexArray& GetVA() const
	{
		return _vArray;
	}
	const VertexBuffer& GetVB() const
	{
		return _vBuffer;
	}
	void SetMaterial(const MaterialID& ID);
	MaterialID GetMaterial() const
	{
		return _material;
	}
	//void SetMaterial(Material* Mat);


	glm::mat4 _modelMat = glm::mat4(1.f);
	//std::shared_ptr<class Shader> _shader;
	//todo temporary: write GetShaderByMaterialParams
	//ShaderID _shaderID = Shader::InvalidShaderID;
};



