#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::AddObjectToScene(const Model& model)
{
	_sceneObjects.push_back(model);
}
