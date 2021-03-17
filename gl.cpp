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
			 0.0f,-0.5f, 0.0f,	  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			 1.0f,-0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
			 0.0f, 0.5f, 0.0f,	  0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
			 1.0f, 0.5f, 0.0f,	  1.0f, 1.0f, 0.0f,	0.0f, 1.0f};

	unsigned int indices [] = {
			 0, 1, 3,
			 1, 2, 3};




	unsigned int shaderProgramLeft, shaderProgramRight;
	LoadShaders("shaders/lessTwo/vertexShaderLeft.src", "shaders/lessTwo/fragmentShaderLeft.src", &shaderProgramLeft);
	LoadShaders("shaders/lessTwo/vertexShaderRight.src", "shaders/lessTwo/fragmentShaderRight.src", &shaderProgramRight);
	

	unsigned int VBOs[2], VAOs[2], EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);
	
	
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeft), verticesLeft, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRight), verticesRight, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	

	//////////////// Загрузка текстуры /////////////////
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char *data = stbi_load("textures/tileTexture.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	
	
	stbi_image_free(data);
	/////////////// Конец загрузки текстуры ///////////
	




	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Отвязываем VBO
	//glBindVertexArray(0); // Отвязываем VAO


	// Цикл рендеринга в окне
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/////////// Левый /////////////////////////////
		glUseProgram(shaderProgramLeft);
		float timeValue		= glfwGetTime();
		float redVAlue		= sin(timeValue) / 2.0f + 0.5f;
		float greenValue 	= -sin(timeValue) / 2.0f + 0.5f;
		float blueValue		= cos(timeValue) / 2.0f + 0.5f;
		std::cout << blueValue<< std::endl;
		int vertexColorLocation = glGetUniformLocation(shaderProgramLeft, "ourColor");
		glUniform4f(vertexColorLocation, redVAlue, greenValue, blueValue, 1.0f);

		float offset = 0.5;
		int zap = glGetUniformLocation(shaderProgramLeft, "uniPos");
		glUniform1f(zap, offset);

		glBindVertexArray(VAOs[0]);  
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//////////////////////////////////////////////


		////////// Правый ////////////////////////////
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgramRight);
		glBindVertexArray(VAOs[1]);  
		
		//verticesRight[4] = sin(timeValue) / 2.0f + 0.5;
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		
		/////////////////////////////////////////////

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();

	return 0;

}

