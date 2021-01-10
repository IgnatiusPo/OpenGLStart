#define _CRT_SECURE_NO_WARNINGS 1
#include "Model.h"
#include <iostream>
#define  HEADER_BUFF_SIZE 80
#include <vector>
#include "VertexBufferLayout.h"
#include "tiny_obj_loader.h"
#include <map>
#include <thread>
#include "Renderer.h"

void Model::AddMesh(const Mesh& mesh)
{
	_meshes.push_back(mesh);
}

void Model::SetModelMatrix(const glm::mat4& ModelMatrix)
{
	for (auto& mesh : _meshes)
	{
		mesh.SetModelMatrix(ModelMatrix);
	}

}

void Model::SetMaterial(const MaterialID& ID)
{
	for (auto& mesh : _meshes)
	{
		mesh.SetMaterial(ID);
	}
}


template<>
Model LoadModel<ModelType::STL>(std::string path)
{
	FILE* file = fopen(path.c_str(), "rb");
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
	Mesh mesh(ModelType::STL, std::move(vArray), std::move(vBuffer));
	Model model;
	model.AddMesh(mesh);
	return model;
};

template<>
Model LoadModel<ModelType::OBJ>(std::string path)
{
	//tinyobj::attrib_t attrib;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;

	//std::string warn;
	//std::string err;

	//bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

	tinyobj::ObjReader reader;
	tinyobj::ObjReaderConfig config;
	config.triangulate = true;
	config.vertex_color = false;

	bool result = reader.ParseFromFile(path, config);

	if (!reader.Valid()) {
		std::cerr << "Failed to load obj file: " << path << std::endl;
		assert(false);
	}

	if (!reader.Warning().empty()) {
		std::cout << "warning: " << reader.Warning() << std::endl;
		//assert(false);
	}

	if (!reader.Error().empty()) {
		std::cerr << "error: " << reader.Error() << std::endl;
		assert(false);
	}

	const tinyobj::attrib_t& attrib = reader.GetAttrib();
	const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();
	const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();



	std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
	std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
	std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2)
		<< std::endl;

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;


	//VertexArray vArray;
	//vArray.Init();
	//VertexBuffer vBuffer;

	//char* Buffer = new char[attrib.vertices.size() * sizeof(Vertex<ModelType::STL>) ]; 

	//vBuffer.Init(PositionAndNormals, NumberOfTriangles * sizeof(Vertex<ModelType::STL>) * 3, NumberOfTriangles * 3);
	////vBuffer.BindData(PositionAndNormals, NumberOfTriangles * sizeof(Vertex<ModelType::STL>) * 3, NumberOfTriangles * 3);
	//vArray.AddBuffer(vBuffer, vLayout);


	Model NewModel;
	using Vertex = Vertex<ModelType::OBJ>;

	VertexBufferLayout vLayout;
	vLayout.Push<float>(3); //position
	vLayout.Push<float>(3); //normal
	vLayout.Push<float>(2); //texcoord

	auto CreateMaterials = [](const std::vector<tinyobj::material_t>& materials) 
	{
		for ( const auto& material : materials )
		{
			MaterialID NewMatID = Renderer::CreateNewMaterial();
			//for test
			//MaterialID NewMatID = Renderer::CreateDefaultPhongMaterial(glm::vec3(1.0f, 0.5f, 0.31f),
			//	glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.2f, 0.2f, 0.2f), 32.f);

			Material* NewMat = Renderer::GetMaterialByID(NewMatID);
			NewMat->properties._mask |= eHasNormal;
			NewMat->properties._mask |= eHasUV;
			if (!material.diffuse_texname.empty())
			{
				NewMat->properties._mask |= eHasDiffuseTexture;
				std::string texturePath = "res/obj/";
				Uniform uniformTexture;
				uniformTexture.type = UniformType::tex;
				uniformTexture.tex.textureID = Renderer::CreateTexture(texturePath + material.diffuse_texname);
				uniformTexture.tex.textureClass = TextureClass::albedo;
				CreateNameForTextureUniform(uniformTexture);
				NewMat->uniforms.push_back(uniformTexture);
			}

			//for tests
			//NewMat->properties._mask |= eDefaultPhongModel;
		}
	};

	MaterialID MaterialOffset = (MaterialID)Renderer::Materials.size();
	CreateMaterials(materials);
	for (const tinyobj::shape_t& shape : shapes) // for each shape
	{
		size_t index_offset = 0;
		//std::vector<Vertex>* vertexData = new std::vector<Vertex>();
		//char* vertexData = new char[sizeof(Vertex) * shape.mesh.indices.size()];
		std::map<int, std::vector<Vertex>> mat_to_vertex;
		for (size_t face = 0; face < shape.mesh.num_face_vertices.size(); ++face) // for each face
		{
			size_t vCount = shape.mesh.num_face_vertices[face];
			int matID = shape.mesh.material_ids[face];

			for (size_t v = 0; v < vCount; ++v) // for each vertex
			{
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
				Vertex vertex;
				size_t vIndex = idx.vertex_index;
				size_t vNormal = idx.normal_index;
				size_t vTexcoord = idx.texcoord_index;

				vertex._position = *((glm::vec3*) & attrib.vertices[vIndex * 3]); // 3 real_t for position
				vertex._normal = *((glm::vec3*) & attrib.normals[vNormal * 3]); // 3 real_t for normal
				vertex._texCoord = *((glm::vec2*) &attrib.texcoords[vTexcoord * 2]); // 2 real_t for texcoord
				size_t offset = (index_offset + v) * sizeof(Vertex);
				mat_to_vertex[matID].push_back(vertex);
			}
			index_offset += vCount;
		}

		for (auto& iterator : mat_to_vertex)
		{
			int matID = iterator.first;
			std::vector<Vertex>& vertexData = iterator.second;
			VertexArray vArray;
			VertexBuffer vBuffer;
			vBuffer.Init(vertexData.data(), (const unsigned int)vertexData.size() * sizeof(Vertex), (const unsigned int)vertexData.size() );
			vArray.AddBuffer(vBuffer, vLayout);
			Mesh NewMesh = Mesh(ModelType::OBJ, std::move(vArray), std::move(vBuffer));

			NewMesh.SetMaterial(MaterialOffset + matID);
			//NewMesh._shaderID = Renderer::(Renderer::GetMaterialByID(MaterialOffset + matID)->properties);
			
			NewModel.AddMesh(NewMesh);

		}

	}


	return NewModel;
};

