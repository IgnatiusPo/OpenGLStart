#pragma once
#include <vector>
//#include <memory>
#include "Scene.h"
#include "Camera.h"

//todo really need this?
#include "Texture.h"

class Application
{
	struct GLFWwindow* _window;
	float _wWidth = 1920.f, _wHeight = 1080.f;
	float _deltaTime = 0.f;
	float _lastFrame = 0.f;
	Scene _scene;

	ShaderID _FSQuadShaderID;
	ShaderID _SkyboxShaderID;
	ShaderID TestShaderID;


	TextureID _CubemapTexture = Texture::InvalidTextureID;

	
public:
	Application();

	int Init();
	void Tick();
	bool ShouldClose();
	void ProcessInput();
	void SwapBuffers();

	void DrawSkyBox(const glm::mat4& view, const glm::mat4& projection);

	~Application();

public:
	float _lastCameraX;
	float _lastCameraY;
	float _fov = 45.f;
	Camera _camera;
};

