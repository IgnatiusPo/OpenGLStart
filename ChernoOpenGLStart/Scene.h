#pragma once
#include "Mesh.h"
#include <vector>
class Scene
{
public:
	std::vector<Mesh> _sceneObjects;
public:
	Scene();
	~Scene();

	void AddObjectToScene(Mesh mesh);
};

