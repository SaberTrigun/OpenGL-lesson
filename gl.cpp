//for compile g++ ogl.cpp glad.c -o bin_ogl -L ./lib/ -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi
#include <iostream>
#include <fstream>
#include <sstream>
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <GL/gl.h>
#include <cmath>
#include "loadShaders.cpp"
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow *window);
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



const unsigned int	SRC_WIDTH = 1000;
const unsigned int	SRC_HEIGHT = 800;






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


	
	// Указывание вершин (и буферов) и настройка вершинных атрибутов
	float verticesLeft[] = {
			-1.0f,-0.5f, 0.0f,	
			 0.0f,-0.5f, 0.0f,	
			-0.5f, 0.5f, 0.0f};

	/*unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3 };
	*/	
	float verticesRight[] = {
			 0.0f,-0.5f, 0.0f,	  1.0f, 0.0f, 0.0f,
			 1.0f,-0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f,	  0.0f, 0.0f, 1.0f} ;
	

	unsigned int shaderProgramLeft, shaderProgramRight;
	LoadShaders("shaders/lessTwo/vertexShaderLeft.src", "shaders/lessTwo/fragmentShaderLeft.src", &shaderProgramLeft);
	LoadShaders("shaders/lessTwo/vertexShaderRight.src", "shaders/lessTwo/fragmentShaderRight.src", &shaderProgramRight);
	

	unsigned int VBOs[2], VAOs[2], EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeft), verticesLeft, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	*/
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRight), verticesRight, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3,  GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Отвязываем VBO
	//glBindVertexArray(0); // Отвязываем VAO


	// Цикл рендеринга в окне
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramLeft);
		float timeValue		= glfwGetTime();
		float greenValue 	= sin(timeValue) / 2.0f + 0.5f;
		std::cout << greenValue << std::endl;
		int vertexColorLocation = glGetUniformLocation(shaderProgramLeft, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		float offset = 0.5;
		int zap = glGetUniformLocation(shaderProgramLeft, "uniPos");
		glUniform1f(zap, offset);

		glBindVertexArray(VAOs[0]);  
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramRight);
		glBindVertexArray(VAOs[1]);  

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();

	return 0;

}

