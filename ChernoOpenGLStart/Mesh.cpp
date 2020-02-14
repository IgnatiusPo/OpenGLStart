#define _CRT_SECURE_NO_WARNINGS 1
#include "Mesh.h"
#include <iostream>
#define  HEADER_BUFF_SIZE 80
#include <vector>
#include "VertexBufferLayout.h"


Mesh::Mesh(void* vertexData, ModelType modelType, VertexArray&& vArray, VertexBuffer&& vBuffer): _vertexData(vertexData), _modelType(modelType), _vArray(vArray), _vBuffer(vBuffer)
{

}


Mesh::Mesh()
{
	assert(false);
}

Mesh::~Mesh()
{
}

void Mesh::UseShader(std::shared_ptr<class Shader> shader)
{
	_shader = shader;
}

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

template<>
Mesh LoadModel<ModelType::STL>(std::string path)
{
	FILE * file = fopen(path.c_str(), "rb");
	char  aBuff[HEADER_BUFF_SIZE];
	fread(aBuff, sizeof(char), HEADER_BUFF_SIZE, file);
	uint32_t NumberOfTriangles = 0;
	fread(reinterpret_cast<void*>(&NumberOfTriangles), sizeof(NumberOfTriangles), 1, file);

	uint32_t offset = 0;

	char* PositionAndNormals = new char[NumberOfTriangles * sizeof(Vertex<ModelType::STL>) * 3]; 

	std::vector<Vertex<ModelType::STL>> vc;
	vc.reserve(NumberOfTriangles * 3);

	for (uint32_t i = 0; i < NumberOfTriangles; ++i)
	{
		//todo maybe store these normals differently?
		float normalBuff[3];
		fread(&normalBuff, sizeof(float) * 3, 1, file);
		fread(PositionAndNormals + offset, sizeof(float) * 3, 1, file);
		offset += sizeof(float) * 3;
		memcpy(PositionAndNormals + offset, normalBuff, sizeof(float) * 3);
		offset += sizeof(float) * 3;

		fread(PositionAndNormals + offset, sizeof(float) * 3, 1, file);
		offset += sizeof(float) * 3;
		memcpy(PositionAndNormals + offset, normalBuff, sizeof(float) * 3);
		offset += sizeof(float) * 3;

		fread(PositionAndNormals + offset, sizeof(float) * 3, 1, file);
		offset += sizeof(float) * 3;
		memcpy(PositionAndNormals + offset, normalBuff, sizeof(float) * 3);
		offset += sizeof(float) * 3;

		fseek(file, sizeof(uint16_t), SEEK_CUR);


		//glm::vec3 normalBuff;
		//fread(&normalBuff, sizeof(float) * 3, 1, file);
		//glm::vec3  vBuff;
		//fread(&vBuff, sizeof(float) * 3, 1, file);

		//vc.emplace_back(vBuff, normalBuff);

		//fread(&vBuff, sizeof(float) * 3, 1, file);


		//vc.emplace_back(vBuff, normalBuff);

		//fread(&vBuff, sizeof(float) * 3, 1, file);


		//vc.emplace_back(vBuff, normalBuff);


		//fseek(file, sizeof(uint16_t), SEEK_CUR);
	}
	
	//std::vector<Vertex<ModelType::STL>> vc;
	//vc.reserve(NumberOfTriangles * 3);
	//for (int i = 0; i < NumberOfTriangles * 3; ++i)
	//{
	//	Vertex<ModelType::STL> vertex;
	//	memcpy(&vertex, PositionAndNormals + ( i * sizeof(Vertex<ModelType::STL>)) , sizeof(Vertex<ModelType::STL>) );
	//	vc.push_back(vertex);
	//}
	//PositionAndNormals = (char*)vc.data();

	VertexArray vArray;
	//vArray.Init();
	VertexBufferLayout vLayout;
	vLayout.Push<float>(3); //position
	vLayout.Push<float>(3); //normal
	VertexBuffer vBuffer;
	vBuffer.Init(PositionAndNormals, NumberOfTriangles * sizeof(Vertex<ModelType::STL>) * 3, NumberOfTriangles * 3);
	//vBuffer.BindData(PositionAndNormals, NumberOfTriangles * sizeof(Vertex<ModelType::STL>) * 3, NumberOfTriangles * 3);
	vArray.AddBuffer(vBuffer, vLayout);
	return Mesh(PositionAndNormals, ModelType::STL,std::move(vArray), std::move(vBuffer));

};

//template<>
//Mesh LoadModel<ModelType::FBX>(std::string path) { assert(false); }; //todo
