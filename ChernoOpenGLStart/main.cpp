//#include <SDL.h>
//#define GLEW_STATIC
#include "Application.h"

int main() 
{

//	GLFWwindow* window;
//	
//	if (!glfwInit())
//		return -1;
//
//	 
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Finally", NULL, NULL);
//	if (!window) {
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	if (glewInit() != GLEW_OK)
//		std::cerr << "Error\n";
//
//
//	glfwSwapInterval(1);
//
//	std::cerr << glGetString(GL_VERSION) << std::endl;
//	{
//
//		float cubePositions[] = {
//			-0.5f, -0.5f, -0.5f,
//			0.5f, -0.5f, -0.5f,
//			0.5f, 0.5f, -0.5f, 
//			-0.5f, 0.5f, -0.5f, 
//
//			-0.5f, -0.5f, 0.5f, 
//			0.5f, -0.5f, 0.5f, 
//			0.5f, 0.5f, 0.5f, 
//			-0.5f, 0.5f, 0.5f, 
//
//			-0.5f, 0.5f, 0.5f, 
//			-0.5f, 0.5f, -0.5f, 
//			-0.5f, -0.5f, -0.5f, 
//
//			0.5f, 0.5f, 0.5f,
//			0.5f, -0.5f, -0.5f, 
//			0.5f, -0.5f, 0.5f, 
//
//			0.5f, -0.5f, -0.5f,
//			-0.5f, 0.5f, 0.5f, 
//		};
//		
//		unsigned int cubeIndices[] = {
//			0, 1, 2, 2, 3, 0,
//			4, 5, 6, 6, 7, 6,
//			8, 9, 10, 10, 4, 8,
//			11, 2, 12, 12, 13, 11,
//			10, 14, 5, 5, 4, 10,
//			3, 2, 11, 11, 15, 3
//		};
//
//		glm::vec3 pointLightPositions[] = {
//			glm::vec3(0.f, 60.f, 20.f),
//			glm::vec3(140.f, 70.f, 30.f)
//		};
//
//		float skyboxVertices[] = {
//			// positions          
//			-1.0f,  1.0f, -1.0f,
//			-1.0f, -1.0f, -1.0f,
//			 1.0f, -1.0f, -1.0f,
//			 1.0f, -1.0f, -1.0f,
//			 1.0f,  1.0f, -1.0f,
//			-1.0f,  1.0f, -1.0f,
//
//			-1.0f, -1.0f,  1.0f,
//			-1.0f, -1.0f, -1.0f,
//			-1.0f,  1.0f, -1.0f,
//			-1.0f,  1.0f, -1.0f,
//			-1.0f,  1.0f,  1.0f,
//			-1.0f, -1.0f,  1.0f,
//
//			 1.0f, -1.0f, -1.0f,
//			 1.0f, -1.0f,  1.0f,
//			 1.0f,  1.0f,  1.0f,
//			 1.0f,  1.0f,  1.0f,
//			 1.0f,  1.0f, -1.0f,
//			 1.0f, -1.0f, -1.0f,
//
//			-1.0f, -1.0f,  1.0f,
//			-1.0f,  1.0f,  1.0f,
//			 1.0f,  1.0f,  1.0f,
//			 1.0f,  1.0f,  1.0f,
//			 1.0f, -1.0f,  1.0f,
//			-1.0f, -1.0f,  1.0f,
//
//			-1.0f,  1.0f, -1.0f,
//			 1.0f,  1.0f, -1.0f,
//			 1.0f,  1.0f,  1.0f,
//			 1.0f,  1.0f,  1.0f,
//			-1.0f,  1.0f,  1.0f,
//			-1.0f,  1.0f, -1.0f,
//
//			-1.0f, -1.0f, -1.0f,
//			-1.0f, -1.0f,  1.0f,
//			 1.0f, -1.0f, -1.0f,
//			 1.0f, -1.0f, -1.0f,
//			-1.0f, -1.0f,  1.0f,
//			 1.0f, -1.0f,  1.0f
//		};
//
//		GLCall(glfwSetFramebufferSizeCallback(window, FrameBufferSize));
//		GLCall(glEnable(GL_BLEND));
//		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//
//		//VertexArray va;
//		//VertexBuffer vb(positions, 16 * 5 * sizeof(float));
//		//VertexBufferLayout layout;
//		//layout.Push<float>(3);
//		//layout.Push<float>(2);
//		//va.AddBuffer(vb, layout);
//
//		//IndexBuffer ib(indices, 36);
//
//	
//		//Shader shader("res/shaders/Basic2.shader");
//		//shader.Bind();
//		//
//		//
//
//		//Texture texture1("res/textures/batman2.png");
//		//texture1.Bind(0);
//		//shader.SetUniform1i("u_Texture1", 0);
//
//		Model obj("res/stl/moon_city_final.STL", true);
//
//		Model obj2("res/stl/Einstein.stl", true);
//
//		//StlData obj3("res/stl/Spiderman_base.stl", true);
//		
//		//////////////////////////////////////////////////////////////////////////////////////////////
//		//ceasar if (obj.DijkstraAlgo(StlData::Vertex(40.7702866, 23.3397827, 1.07599068), StlData::Vertex(43.7950211, 5.68451834, 7.95413637)) == -1)
//		// 		
//		// if (obj.DijkstraAlgo(StlData::Vertex(44.9034500, 1.99257922, 5.80117512), StlData::Vertex(52.8352776, 23.1350098, 1.07599068)) == -1)
//		// moon_city (StlData::Vertex(-63.2675362,32.7694702, 51.1924706), StlData::Vertex(-5.75104618, 51.7455826, 35.2884789)
//
// 		//if (obj.DijkstraAlgo(StlData::vec3(-63.2675362, 32.7694702, 51.1924706), StlData::vec3(-5.75104618, 51.7455826, 35.2884789)) == -1)
//			//return 0;
//			
//		unsigned int dijkstraPosSize;
//		const void* dijkstraPositions = obj.GetDijkstraPositions(dijkstraPosSize);
//
//		//////////////////////////////////////////////////////////////////////////////////////////////
//		// 22.0851345 47.9234886 24.0000000           // 46.0914383 15.2318153 20.6702518       // 32.5483475  1.65903008  22.0488968     sphere
//		// 
//
//		RenderObject rObject(&obj);
//		RenderObject rObject2(&obj2);
//		//RenderObject rObject3(&obj3);
//				
//
//
//		BaseLightShader shaderObject("res/shaders/Dijkstra.shader");
//		//Shader shaderObject("res/shaders/DepthOnly.shader");
//		rObject.UseShader(&shaderObject);
//		rObject2.UseShader(&shaderObject);
//		//rObject3.UseShader(&shaderObject);
//		/////////// lamp
//		VertexArray vaLamp;
//		VertexBuffer vbLamp(cubePositions, 16 * 3 *  sizeof(float));
//		VertexBufferLayout lampLayout;
//		lampLayout.Push<float>(3);
//		vaLamp.AddBuffer(vbLamp, lampLayout);
//		IndexBuffer ibLamp(cubeIndices, 36);
//		vaLamp.Unbind();
//
//		Shader shaderLamp("res/shaders/Lamp.shader");
//
//
//
//		//VertexArray vaDijkstra;
//		//VertexBuffer vbDijkstra(dijkstraPositions, dijkstraPosSize);
//		//VertexBufferLayout dijkstraLayout;
//		//dijkstraLayout.Push<float>(3);
//		//vaDijkstra.AddBuffer(vbDijkstra, dijkstraLayout);
//		//vaDijkstra.Unbind();
//
//		//skybox
//		VertexArray vaSkybox;
//		VertexBuffer vbSkybox(skyboxVertices, 36 * 3 * sizeof(float));
//		VertexBufferLayout vblSkybox;
//		vblSkybox.Push<float>(3);
//		vaSkybox.AddBuffer(vbSkybox, vblSkybox);
//		vaSkybox.Unbind();
//		Shader shaderSkybox("res/shaders/Skybox.shader");
//		std::vector<std::string> faces
//		{
//			"res/textures/skybox/right.jpg",
//			"res/textures/skybox/left.jpg",
//			"res/textures/skybox/top.jpg",
//			"res/textures/skybox/bottom.jpg",
//			"res/textures/skybox/front.jpg",
//			"res/textures/skybox/back.jpg"
//		};
//		Cubemap cubemapTexture(faces);
//
//		Renderer renderer;
//		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_LESS);
//
////draw loop		
//		while (!glfwWindowShouldClose(window))
//		{
//			shaderObject.Bind();
//			glLineWidth(1.0f);
//			//glPointSize(50.0f);
//			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			//glClearColor(0.5f, 0.5f, 0.5f, 1.f);
//			renderer.Clear();
//			float CurrentFrame = glfwGetTime();
//			deltaTime = CurrentFrame - lastFrame;
//			lastFrame = CurrentFrame;
//			
//			processInput(window);
//
//		
//			
//			glm::mat4 view = glm::mat4(1.0f);
//			view = camera.GetViewMatrix();
//
//			glm::mat4 projection = glm::mat4(1.0f);
//			projection = glm::perspective(glm::radians(fov), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 500.f);
//
//			shaderObject.Bind();
//			shaderObject.UpdateViewMatrix(view);
//			shaderObject.UpdateProjectionMatrix(projection);
//			//shaderObject.SetUniformMat4f("u_View", view);
//			//shaderObject.SetUniformMat4f("u_Projection", projection);
//			
//			shaderObject.UpdateuViewPositionMatrix(camera._position);
//			shaderObject.SetPointLightPositions(pointLightPositions);
//			//shaderObject.SetUniform3f("u_ViewPosition", camera._position);
//
//////////////////////////////////////////////////////////// main test
//			glm::mat4 model = glm::mat4(1.0f);
//			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
//			model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
//			model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1.f, 0.f, 0.f));
//			shaderObject.UpdateModelMatrix(model);
//			//shaderObject.SetUniformMat4f("u_Model", model);
//			rObject.Draw();
//
//			model = glm::mat4(1.f);
//			model = glm::translate(model, glm::vec3(150.f, 0.f, 0.f));
//			model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
//			shaderObject.UpdateModelMatrix(model);
//			//shaderObject.SetUniformMat4f("u_Model", model);
//
//			rObject2.Draw();
//
//			//model = glm::mat4(1.f);
//			//model = glm::translate(model, glm::vec3(-150.f, 0.f, 0.f));
//			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
//			//model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
//			//model = glm::translate(model, glm::vec3(0.f, 0.f, -100.f));
//			//shaderObject.UpdateModelMatrix(model);
//			//shaderObject.SetUniformMat4f("u_Model", model);
//
//			//rObject3.Draw();
////////////////////////////////////////////////////////////// main end
//
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			//draw cube
//			//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
//			shaderLamp.Bind();
//			shaderLamp.SetUniformMat4f("u_View", view);
//			shaderLamp.SetUniformMat4f("u_Projection", projection);
//			shaderLamp.SetUniform4f("u_LampColor", lampColor);
//			vaLamp.Bind();
//			ibLamp.Bind();
//
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, pointLightPositions[0]);
//			model = glm::scale(model, glm::vec3(3.f, 3.f, 3.f));
//			shaderLamp.SetUniformMat4f("u_Model", model);
//			shaderLamp.SetUniform4f("u_LampColor", lampColor);
//			renderer.Draw(vaLamp, ibLamp, shaderLamp);
//			
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, pointLightPositions[1]);
//			//model = glm::scale(model, glm::vec3(3.f, 3.f, 3.f));
//			shaderLamp.SetUniformMat4f("u_Model", model);
//			shaderLamp.SetUniform4f("u_LampColor", 0.0f, 1.f, 0.66f, 1.f);
//			renderer.Draw(vaLamp, ibLamp, shaderLamp);
//
//			vaLamp.Unbind();
//			ibLamp.Unbind();
//
//
//			
//			////////////////////////////////////////////////////////////////////////
//			//Dijkstra path 
//			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//
//			//model = glm::mat4(1.0f);
//
//			//view = glm::mat4(1.0f);
//			//view = camera.GetViewMatrix();
//			//view = glm::rotate(view, glm::radians(-90.f), glm::vec3(1.f, 0.0f, 0.0f));
//
//			//projection = glm::mat4(1.0f);
//			//projection = glm::perspective(glm::radians(fov), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 500.f);
//
//			//shaderObject.Bind();  
//			//shaderObject.SetUniformMat4f("u_View", view);
//			//shaderObject.SetUniformMat4f("u_Projection", projection);
//			//shaderObject.SetUniformMat4f("u_Model", model);
//			//shaderObject.SetUniform4f("u_ObjectColor", 0.0f, 1.f, 1.f, 1.0f);
//			//shaderObject.SetUniform4f("u_LightColor", lampColor);
//
//			//shaderObject.SetUniform3f("u_LightPosition", lightPos);
//			//shaderObject.SetUniform3f("u_ViewPosition", camera._position);
//			//shaderObject.SetUniform1f("u_SpecularStrength", .5f);
//
//
//
//			//glLineWidth(50.0f);
//
//			//vaDijkstra.Bind();
//			//glDrawArrays(GL_LINE_STRIP, 0, dijkstraPosSize / (3 * sizeof(float)));
//			
//
//			//skybox	
//			shaderSkybox.Bind();
//			cubemapTexture.Bind();
//			glDepthFunc(GL_LEQUAL);
//			shaderSkybox.SetUniformMat4f("u_Projection", projection);
//			shaderSkybox.SetUniformMat4f("u_View", view);
//			vaSkybox.Bind();
//			renderer.Draw(vaSkybox, shaderSkybox, 0, 36);
//
//			glDepthFunc(GL_LESS);
//
//			glfwSwapBuffers(window);
//			glfwPollEvents();
//		}
//	}
//	glfwTerminate();

	Application app;
	app.Init();
	while (!app.ShouldClose())
	{
		app.Tick();
	}


	return 0;
}

//void processInput(GLFWwindow *window)
//{
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboardInput(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboardInput(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboardInput(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboardInput(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
//		GShaderState = GlobalShaderState::NORMAL;
//	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
//		GShaderState = GlobalShaderState::DEPTH_ONLY;
//}
//
//void mouse_callback(GLFWwindow *window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastCameraX = xpos;
//		lastCameraY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastCameraX;
//	float yoffset = lastCameraY - ypos;
//	lastCameraX = xpos;
//	lastCameraY = ypos;
//
//	camera.ProcessMouseInput(xoffset, yoffset);
//}
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
//{
//	camera.ProcessScrollInput(yoffset, fov);
//}
