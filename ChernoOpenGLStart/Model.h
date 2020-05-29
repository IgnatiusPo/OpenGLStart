#pragma once
#include "Mesh.h"

class Model
{
public:
	std::vector<Mesh> _meshes;

	void AddMesh(const Mesh& mesh);

	void SetModelMatrix(const glm::mat4& ModelMatrix);
	void SetMaterial(const MaterialID& ID);
	
	//sets shader to use for ALL of the submeshes. Usefull
	void SetShader(const ShaderID& ID);
	ShaderID _uniteShader = Shader::InvalidShaderID;
};




template<ModelType T>
Model LoadModel(std::string path);

//todo maybe
//template<ModelType T>
//MaterialID CreateDefaultMeshMaterial();