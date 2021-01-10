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
	float _shadowWidth = 1024.f, _shadowHeight = 1024.f;
	float _deltaTime = 0.f;
	float _lastFrame = 0.f;
	Scene _scene;

	ShaderID _FSQuadShaderID;
	ShaderID _SkyboxShaderID;
	ShaderID TestShaderID;


	TextureID _CubemapTexture = Texture::InvalidTextureID;
	//todo
	//TextureID _ShadowmapTexture = Texture::InvalidTextureID;

	unsigned int shadowMapFBO = 0xF;
	unsigned int shadowMapTexture = 0xF;
	
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
	//todo global uniform buffer
	glm::vec3 _dirLightDirection = glm::vec3(0.2f, -1.f, 0.3f);
};

