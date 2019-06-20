//#include <SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Texture.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "StlData.h"
#include <thread>
#include "RenderObject.h"
const float WINDOW_WIDTH = 1920;
const float WINDOW_HEIGHT = 1080;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastCameraX = WINDOW_WIDTH / 2;
float lastCameraY = WINDOW_HEIGHT / 2;
float fov = 45.f;
glm::vec3 lightPos(0.f, 0.f, 0.f);
glm::vec4 lampColor(1.0f, 1.0f, 1.0f, 1.0f);
Camera camera(glm::vec3(0.f, 100.f, 100.f));

void FrameBufferSize(GLFWwindow* window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}


void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double ypos);

int main() 
{

	GLFWwindow* window;
	
	if (!glfwInit())
		return -1;

	 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Finally", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Error\n";


	glfwSwapInterval(1);

	std::cerr << glGetString(GL_VERSION) << std::endl;
	{

		float cubePositions[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f, 
			-0.5f, 0.5f, -0.5f, 

			-0.5f, -0.5f, 0.5f, 
			0.5f, -0.5f, 0.5f, 
			0.5f, 0.5f, 0.5f, 
			-0.5f, 0.5f, 0.5f, 

			-0.5f, 0.5f, 0.5f, 
			-0.5f, 0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 

			0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, 0.5f, 

			0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f, 
		};
		
		unsigned int cubeIndices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 6,
			8, 9, 10, 10, 4, 8,
			11, 2, 12, 12, 13, 11,
			10, 14, 5, 5, 4, 10,
			3, 2, 11, 11, 15, 3
		};

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.f, 60.f, 20.f),
			glm::vec3(140.f, 70.f, 30.f)
		};

		GLCall(glfwSetFramebufferSizeCallback(window, FrameBufferSize));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		//VertexArray va;
		//VertexBuffer vb(positions, 16 * 5 * sizeof(float));
		//VertexBufferLayout layout;
		//layout.Push<float>(3);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);

		//IndexBuffer ib(indices, 36);

	
		//Shader shader("res/shaders/Basic2.shader");
		//shader.Bind();
		//
		//

		//Texture texture1("res/textures/batman2.png");
		//texture1.Bind(0);
		//shader.SetUniform1i("u_Texture1", 0);

		//Texture texture2("res/textures/batman3.png");
		//texture2.Bind(1);
		//shader.SetUniform1i("u_Texture2", 1);

		//Renderer renderer;

		//texture1.Bind(0);
		//texture2.Bind(1);

		//glEnable(GL_DEPTH_TEST);

		//glm::vec3 cubeTranslations[] = {
		//	glm::vec3(0.0f,  0.0f,  0.0f),
		//	glm::vec3(.20f,  .50f, -1.50f),
		//	glm::vec3(-1.5f, -2.2f, -2.5f),
		//	glm::vec3(-3.8f, -2.0f, -12.3f),
		//	glm::vec3(2.4f, -0.4f, -3.5f),
		//	glm::vec3(-1.7f,  3.0f, -7.5f),
		//	glm::vec3(1.3f, -2.0f, -2.5f),
		//	glm::vec3(1.5f,  2.0f, -2.5f),
		//	glm::vec3(1.5f,  0.2f, -1.5f),
		//	glm::vec3(-1.3f,  1.0f, -1.5f)
		//};

	

		StlData obj("res/stl/moon_city_final.STL", true);

		StlData obj2("res/stl/Einstein.stl", true);

		//StlData obj3("res/stl/Spiderman_base.stl", true);
		
		//////////////////////////////////////////////////////////////////////////////////////////////
		//ceasar if (obj.DijkstraAlgo(StlData::Vertex(40.7702866, 23.3397827, 1.07599068), StlData::Vertex(43.7950211, 5.68451834, 7.95413637)) == -1)
		// 		
		// if (obj.DijkstraAlgo(StlData::Vertex(44.9034500, 1.99257922, 5.80117512), StlData::Vertex(52.8352776, 23.1350098, 1.07599068)) == -1)
		// moon_city (StlData::Vertex(-63.2675362,32.7694702, 51.1924706), StlData::Vertex(-5.75104618, 51.7455826, 35.2884789)

 		//if (obj.DijkstraAlgo(StlData::vec3(-63.2675362, 32.7694702, 51.1924706), StlData::vec3(-5.75104618, 51.7455826, 35.2884789)) == -1)
			//return 0;
			
		unsigned int dijkstraPosSize;
		const void* dijkstraPositions = obj.GetDijkstraPositions(dijkstraPosSize);

		//////////////////////////////////////////////////////////////////////////////////////////////
		// 22.0851345 47.9234886 24.0000000           // 46.0914383 15.2318153 20.6702518       // 32.5483475  1.65903008  22.0488968     sphere
		// 

		RenderObject rObject(&obj);
		RenderObject rObject2(&obj2);
		//RenderObject rObject3(&obj3);
				


		Shader shaderObject("res/shaders/Dijkstra.shader");
		rObject.UseShader(&shaderObject);
		rObject2.UseShader(&shaderObject);
		//rObject3.UseShader(&shaderObject);
		/////////// lamp
		VertexArray vaLamp;
		VertexBuffer vbLamp(cubePositions, 16 * 3 *  sizeof(float));
		VertexBufferLayout lampLayout;
		lampLayout.Push<float>(3);
		vaLamp.AddBuffer(vbLamp, lampLayout);
		IndexBuffer ibLamp(cubeIndices, 36);
		vaLamp.Unbind();

		Shader shaderLamp("res/shaders/Lamp.shader");



		VertexArray vaDijkstra;
		VertexBuffer vbDijkstra(dijkstraPositions, dijkstraPosSize);
		VertexBufferLayout dijkstraLayout;
		dijkstraLayout.Push<float>(3);
		vaDijkstra.AddBuffer(vbDijkstra, dijkstraLayout);
		vaDijkstra.Unbind();

		Renderer renderer;
		glEnable(GL_DEPTH_TEST);


		
//draw loop		
		int progressiveSize = 3;
		while (!glfwWindowShouldClose(window))
		{


			shaderObject.Bind();
			glLineWidth(1.0f);
			//glPointSize(50.0f);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glClearColor(0.5f, 0.5f, 0.5f, 1.f);
			renderer.Clear();
			float CurrentFrame = glfwGetTime();
			deltaTime = CurrentFrame - lastFrame;
			lastFrame = CurrentFrame;
			
			processInput(window);


		
			
			glm::mat4 view = glm::mat4(1.0f);
			view = camera.GetViewMatrix();

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(fov), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 500.f);

			shaderObject.Bind();
			shaderObject.SetUniformMat4f("u_View", view);
			shaderObject.SetUniformMat4f("u_Projection", projection);
			//material	
			shaderObject.SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
			shaderObject.SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
			shaderObject.SetUniform3f("material.specular", 0.2f, 0.2f, 0.2f);
			shaderObject.SetUniform1f("material.shininess",32);
			
			//directional light
			shaderObject.SetUniform3f("dirLight.direction", -0.2f, -1.f, -0.3f);
			shaderObject.SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			shaderObject.SetUniform3f("dirLight.diffuse", .2f, .2f, .2f);
			shaderObject.SetUniform3f("dirLight.specular", .5f, .5f, .5f);
				
			//point lights
			shaderObject.SetUniform3f("pointLights[0].position", pointLightPositions[0]);
			shaderObject.SetUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
			shaderObject.SetUniform3f("pointLights[0].diffuse", 1.f, 1.f, 1.f);
			shaderObject.SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
			shaderObject.SetUniform1f("pointLights[0].constant", 1.0f);
			shaderObject.SetUniform1f("pointLights[0].linear", 0.014f);
			shaderObject.SetUniform1f("pointLights[0].quadratic", 0.0007f);
			
			shaderObject.SetUniform3f("pointLights[1].position", pointLightPositions[1]);
			shaderObject.SetUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
			shaderObject.SetUniform3f("pointLights[1].diffuse", 0.f, 3.f, 2.f);
			shaderObject.SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
			shaderObject.SetUniform1f("pointLights[1].constant", 1.0f);
			shaderObject.SetUniform1f("pointLights[1].linear", 0.09);
			shaderObject.SetUniform1f("pointLights[1].quadratic", 0.032f);





			shaderObject.SetUniform3f("u_ViewPosition", camera._position);

////////////////////////////////////////////////////////// main test
			glm::mat4 model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
			model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1.f, 0.f, 0.f));
			shaderObject.SetUniformMat4f("u_Model", model);
			
			rObject.Draw();

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(150.f, 0.f, 0.f));
			model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
			shaderObject.SetUniformMat4f("u_Model", model);

			rObject2.Draw();

			model = glm::mat4(1.f);
			//model = glm::translate(model, glm::vec3(-150.f, 0.f, 0.f));
			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
			//model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
			model = glm::translate(model, glm::vec3(0.f, 0.f, -100.f));
			shaderObject.SetUniformMat4f("u_Model", model);

			//rObject3.Draw();
//////////////////////////////////////////////////////////// main end


			///////////////////////////////////////////////////////////////////////////////////////
			//draw cube
			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
			shaderLamp.Bind();
			shaderLamp.SetUniformMat4f("u_View", view);
			shaderLamp.SetUniformMat4f("u_Projection", projection);
			shaderLamp.SetUniform4f("u_LampColor", lampColor);
			vaLamp.Bind();
			ibLamp.Bind();

			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[0]);
			model = glm::scale(model, glm::vec3(3.f, 3.f, 3.f));
			shaderLamp.SetUniformMat4f("u_Model", model);
			shaderLamp.SetUniform4f("u_LampColor", lampColor);
			renderer.Draw(vaLamp, ibLamp, shaderLamp);
			
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[1]);
			//model = glm::scale(model, glm::vec3(3.f, 3.f, 3.f));
			shaderLamp.SetUniformMat4f("u_Model", model);
			shaderLamp.SetUniform4f("u_LampColor", 0.0f, 1.f, 0.66f, 1.f);
			renderer.Draw(vaLamp, ibLamp, shaderLamp);

			vaLamp.Unbind();
			ibLamp.Unbind();



			////////////////////////////////////////////////////////////////////////
			//Dijkstra path 
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			//model = glm::mat4(1.0f);

			//view = glm::mat4(1.0f);
			//view = camera.GetViewMatrix();
			//view = glm::rotate(view, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));

			//projection = glm::mat4(1.0f);
			//projection = glm::perspective(glm::radians(fov), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 500.f);

			//shaderObject.Bind();  
			//shaderObject.SetUniformMat4f("u_View", view);
			//shaderObject.SetUniformMat4f("u_Projection", projection);
			//shaderObject.SetUniformMat4f("u_Model", model);
			//shaderObject.SetUniform4f("u_ObjectColor", 0.0f, 1.f, 1.f, 1.0f);
			//shaderObject.SetUniform4f("u_LightColor", lampColor);

			//shaderObject.SetUniform3f("u_LightPosition", lightPos);
			//shaderObject.SetUniform3f("u_ViewPosition", camera._position);
			//shaderObject.SetUniform1f("u_SpecularStrength", .5f);



			//glLineWidth(50.0f);

			//vaDijkstra.Bind();
			//glDrawArrays(GL_LINE_STRIP, 0, dijkstraPosSize / (3 * sizeof(float)));
			

			


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboardInput(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboardInput(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboardInput(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboardInput(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastCameraX = xpos;
		lastCameraY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastCameraX;
	float yoffset = lastCameraY - ypos;
	lastCameraX = xpos;
	lastCameraY = ypos;

	camera.ProcessMouseInput(xoffset, yoffset);
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.ProcessScrollInput(yoffset, fov);
}
