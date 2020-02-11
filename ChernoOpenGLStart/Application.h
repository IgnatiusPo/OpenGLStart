#pragma once
#include <vector>
#include "Scene.h"
#include "Camera.h"



class Application
{
	struct GLFWwindow* _window;
	float _wWidth = 1920.f, _wHeight = 1080.f;
	float _deltaTime = 0.f;
	float _lastFrame = 0.f;
	Scene _scene;
	glm::vec3 _dirLightDirection;
	bool bShouldClose = false;

	std::shared_ptr<Shader> FSQuadShader;
public:
	Application();

	int Init();
	void Tick();
	bool ShouldClose();
	void ProcessInput();
	void SwapBuffers();

	~Application();

public:
	float _lastCameraX;
	float _lastCameraY;
	float _fov = 45.f;
	Camera _camera;
};

