//for compile g++ ogl.cpp glad.c -o bin_ogl -L ./lib/ -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi
#include <iostream>
#include <fstream>
#include <sstream>
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
// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
unsigned int SRC_WIDTH	= 800;
unsigned int SRC_HEIGHT	= 600;

	


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

	// glad загрузка всех указателей на OpenGL-функции
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed initialize GLAD" << std::endl;
		return -1;
	}

	float vertices[] = {
    // координаты         // цвета
	 0.5f, -0.5f, 0.0f,   // нижняя правая вершина
	-0.5f, -0.5f, 0.0f,   // нижняя левая вершина
	 0.0f,  0.5f, 0.0f};    // верхняя вершина
 


	Shader vertexShader, fragmentShader, shaderProg;
	vertexShader.loadCompileShader("shaders/lessTwo/vertexShaderLeft.src", "vertex");
	fragmentShader.loadCompileShader("shaders/lessTwo/fragmentShaderLeft.src", "fragment");
	shaderProg.createProgram(vertexShader, fragmentShader);
	shaderProg.deleteShader(vertexShader, fragmentShader);


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	// Цикл рендеринга в окне
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProg.useProgram();
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		shaderProg.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
    		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;

}

