#include <GL/glew.h>
#include "Application.h"
#include "Macroses.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"


namespace Callbacks
{
	void mouse_callback(GLFWwindow *window, double xpos, double ypos)
	{
		Application* app = (Application*)(glfwGetWindowUserPointer(window));
		
		static bool firstMouse = true;
		if (firstMouse)
		{
			app->_lastCameraX = (float)xpos;
			app->_lastCameraY = (float)ypos;
			firstMouse = false;
		}
		
		float xoffset = (float)xpos - app->_lastCameraX;
		float yoffset = app->_lastCameraY - (float)ypos;
		app->_lastCameraX = (float)xpos;
		app->_lastCameraY = (float)ypos;

		app->_camera.ProcessMouseInput(xoffset, yoffset);
	}

	void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
	{
		Application* app = (Application*)(glfwGetWindowUserPointer(window));
		app->_camera.ProcessScrollInput((float)yoffset, app->_fov);
	}
	void FrameBufferSize(GLFWwindow* window, int Width, int Height)
	{
		GLCall(glViewport(0, 0, Width, Height));
	}
}

Application::Application()
{
	_camera = Camera(glm::vec3(0.f, 100.f, 100.f));
}


int Application::Init()
{
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow((int)_wWidth, (int)_wHeight, "Application", NULL, NULL);
	if (!_window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_window);
	//GLCall(glViewport(0, 0, _wWidth, _wHeight));
	GLCall(glfwSetFramebufferSizeCallback(_window, Callbacks::FrameBufferSize));

	if (glewInit() != GLEW_OK)
		return -1;


	glfwSetWindowUserPointer(_window, this);

	glfwSwapInterval(1);

	Renderer::Init();
	
	//skybox
	std::vector<std::string> faces
	{
		"res/textures/skybox/right.jpg",
		"res/textures/skybox/left.jpg",
		"res/textures/skybox/top.jpg",
		"res/textures/skybox/bottom.jpg",
		"res/textures/skybox/front.jpg",
		"res/textures/skybox/back.jpg"
	};
	_CubemapTexture = Renderer::CreateCubemapTexture(faces);

	//scene
	_scene.AddObjectToScene(LoadModel<ModelType::STL>("res/stl/Einstein.stl"));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	_scene._sceneObjects[0].SetModelMatrix(model);
	_scene.AddObjectToScene(LoadModel<ModelType::STL>("res/stl/moon_city_final.stl"));
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(200.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	_scene._sceneObjects[1].SetModelMatrix(model);

	//todo think about proper material and uniform handling
	std::shared_ptr<Shader> DefaultShader = std::shared_ptr<Shader>(new Shader("res/shaders/BasicVert.shader", "res/shaders/PhongFrag.shader"));
	DefaultShader->Bind();

	//material	
	DefaultShader->SetUniform("material.ambient", 1.0f, 0.5f, 0.31f);
	DefaultShader->SetUniform("material.diffuse", 1.0f, 0.5f, 0.31f);
	DefaultShader->SetUniform("material.specular", 0.2f, 0.2f, 0.2f);
	DefaultShader->SetUniform("material.shininess", 32.f);

	//directional light
	DefaultShader->SetUniform("dirLight.direction", -0.2f, -1.f, 0.3f);
	DefaultShader->SetUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	DefaultShader->SetUniform("dirLight.diffuse", .5f, .5f, .5f);
	DefaultShader->SetUniform("dirLight.specular", 1.5f, 1.5f, 1.5f);

	_scene._sceneObjects[0]._shader = DefaultShader;
	_scene._sceneObjects[1]._shader = DefaultShader;

	//special shaders
	_FSQuadShader = std::shared_ptr<Shader>(new Shader("res/shaders/QuadVert.shader", "res/shaders/SimpleColorFrag.shader"));
	_SkyboxShader = std::shared_ptr<Shader>(new Shader("res/shaders/SkyboxVert.shader", "res/shaders/SkyboxFrag.shader"));

	//Testing here
	TestShader = std::shared_ptr<Shader>(new Shader("res/shaders/Simple3floatVert.shader", "res/shaders/SimpleColorFrag.shader"));

	
	return 0;
}

void Application::Tick()
{
	float CurrentFrame = (float)glfwGetTime();
	_deltaTime = CurrentFrame - _lastFrame;
	_lastFrame = CurrentFrame;
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	Renderer::Clear();
	glfwPollEvents();
	ProcessInput();
	
	glm::mat4 view = glm::mat4(1.0f);
	view = _camera.GetViewMatrix();

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(_fov), _wWidth / _wHeight, 0.1f, 500.f); //todo setup near and far properly

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//todo: maybe i can calculate everything in viewSpace so i don't need to care about ViewPosition in World Space?
	Renderer::Draw(_scene, view, projection, _camera._position);


	GLCall(glDepthFunc(GL_LEQUAL));
	DrawSkyBox(view, projection);
	//Renderer::DrawCube(glm::mat4(1.f), projection, view, TestCubeShader);
	//FSQuadShader->Bind();
	//Renderer::DrawQuadFS();
	


	SwapBuffers();
}

bool Application::ShouldClose()
{
	return glfwWindowShouldClose(_window);
}

void Application::ProcessInput()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_window, Callbacks::mouse_callback);
	glfwSetScrollCallback(_window, Callbacks::scroll_callback);

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		GLCall(glfwSetWindowShouldClose(_window, GLFW_TRUE ));
	}

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera.ProcessKeyboardInput(FORWARD, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera.ProcessKeyboardInput(BACKWARD, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera.ProcessKeyboardInput(LEFT, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera.ProcessKeyboardInput(RIGHT, _deltaTime);

}

void Application::SwapBuffers()
{
	//GLCall(glfwMakeContextCurrent(_window));
	GLCall(glfwSwapBuffers(_window));
}

void Application::DrawSkyBox(const glm::mat4& view, const glm::mat4& projection)
{
	Cubemap* CubemapTex = Renderer::GetCubemapTextureByID(_CubemapTexture);
	CubemapTex->Bind(0);


	Renderer::DrawCube(projection, view, _SkyboxShader);
}

Application::~Application()
{

	//GLCall(glfwDestroyWindow(_window));
	//GLCall(glfwTerminate());
	//todo check the error
	glfwTerminate();
}


