//for compile g++ ogl.cpp glad.c -o bin_ogl -L ./lib/ -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi
#include <iostream>
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <GL/gl.h>
#include <cmath>
#include "loadShaders.cpp"
#include "stb_image.h"
#include "include/glm/glm/glm.hpp"
#include "include/glm/glm/gtc/matrix_transform.hpp"
#include "include/glm/glm/gtc/type_ptr.hpp"
#include "shaderClass.cpp"
#include "cameraClass.cpp"
#include "controlsFunc.cpp"

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


float deltaTime = 0.0f;
float lastFrame = 0.0f;
unsigned int SRC_WIDTH	= 800;
unsigned int SRC_HEIGHT	= 600;
float lastX = SRC_WIDTH / 2.0f;
float lastY = SRC_HEIGHT / 2.0f;
bool firstMouse = true;

	


//Camera cam(glm::vec3(0.0f, 0.0f, 3.0f)); ОПРЕДЕЛЕНА В CONTROLS.h 



int main() {
	// glfw инициализация и конфигурирование
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
	// glfw Создание окна
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "OpenGL Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	// glad загрузка всех указателей на OpenGL-функции
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f };



	Shader vertexShaderCube, fragmentShaderCube, shaderProgCube, vertexShaderLight, fragmentShaderLight, shaderProgLight;
	//Куб
	vertexShaderCube.loadCompileShader("shaders/lessEight/vertexShaderCube.src", VERTEX);
	fragmentShaderCube.loadCompileShader("shaders/lessEight/fragmentShaderCube.src", FRAGMENT);
	//Лампа
	vertexShaderLight.loadCompileShader("shaders/lessEight/vertexShaderLight.src", VERTEX);
	fragmentShaderLight.loadCompileShader("shaders/lessEight/fragmentShaderLight.src", FRAGMENT);
	//Создаём шейдерную программу
	shaderProgCube.createProgram(vertexShaderCube, fragmentShaderCube);
	shaderProgLight.createProgram(vertexShaderLight, fragmentShaderLight);
	//Удаляем шейдеры
	shaderProgCube.deleteShader(vertexShaderCube, fragmentShaderCube);
	shaderProgLight.deleteShader(vertexShaderLight, fragmentShaderLight);


	unsigned int cubeVAO, lightVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	shaderProgCube.useProgram();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH/(float)SRC_HEIGHT, 0.1f, 100.0f);
	shaderProgCube.setMat4("projection", projection);
	shaderProgLight.useProgram();
	shaderProgLight.setMat4("projection", projection);



	// Цикл рендеринга в окне
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		float lightPos_x = 1.0f + sin(glfwGetTime()) * 2.0f;
		float lightPos_y = sin(glfwGetTime() / 2.0f) * 1.0f;

		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
///////////////////////////////////////////////////////////////////////////////////////////
		shaderProgCube.useProgram();
		
		shaderProgCube.setVec3("lightPos", 1.2f, 1.0f, 2.0f);
		shaderProgCube.setVec3("viewPos", cam.position);

		shaderProgCube.setVec3("light.ambient", 0.5f, 0.8f, 0.1f);
		shaderProgCube.setVec3("light.diffuse", 0.3f, 0.2f, 0.7f);
		shaderProgCube.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		

		shaderProgCube.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		shaderProgCube.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		shaderProgCube.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shaderProgCube.setFloat("material.shininess", 32.0f);

//		shaderProgCube.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//		shaderProgCube.setVec3("lightColor", 1.0f, 1.0f, 1.0f);


		glm::mat4 model = glm::mat4(1.0f);
		shaderProgLight.setMat4("model", model);

		glm::mat4 view = cam.getViewMatrix();
		shaderProgLight.setMat4("view", view);	


		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
		shaderProgLight.useProgram();
		
		model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(lightPos_x, lightPos_y, 2.0f));

		model = scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		
		shaderProgLight.setMat4("model", model);
		shaderProgLight.setMat4("view", view);



		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
//////////////////////////////////////////////////////////////////////////////////////////

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	

	return 0;

}

