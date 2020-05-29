#include "Mesh.h"
Mesh::Mesh( ModelType modelType, VertexArray&& vArray, VertexBuffer&& vBuffer): _modelType(modelType), _vArray(vArray), _vBuffer(vBuffer)
{

}


Mesh::Mesh()
{
	//assert(false);
}

Mesh::~Mesh()
{
}

//void Mesh::UseShader(std::shared_ptr<class Shader> shader)
//{
//	_shader = shader;
//}

void Mesh::SetModelMatrix(glm::mat4 ModelMatrix)
{
	_modelMat = ModelMatrix;
}

void Mesh::SetMaterial(const MaterialID& ID)
{
	_material = ID;
}

//void Mesh::SetMaterial(Material* Mat)
//{
//
//}



