#pragma once
#include "Mesh.h"

class Model
{
public:
	std::vector<Mesh> _meshes;

	void AddMesh(const Mesh& mesh);

	void SetModelMatrix(const glm::mat4& ModelMatrix);
	void SetMaterial(const MaterialID& ID);
	
};




template<ModelType T>
Model LoadModel(std::string path);

//todo maybe
//template<ModelType T>
//MaterialID CreateDefaultMeshMaterial();