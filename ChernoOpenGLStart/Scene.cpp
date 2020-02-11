#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::AddObjectToScene(Mesh mesh)
{
	_sceneObjects.push_back(mesh);
}
