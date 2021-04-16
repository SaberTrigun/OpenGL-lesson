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
unsigned int SRC_WIDTH	= 800;
unsigned int SRC_HEIGHT	= 600;


	class Shader{
		private:
			unsigned int 	typeShader, shaderProgram;
			std::string	shaderSrc;
			int 		success;
			char 		infolog [512];
			char const* 	shaderSrcPtr;
			//std::ifstream	shaderStream;
		public:
			void loadCompileShader(const char* shaderFilePath, std::string typeShaderIn){
				if (typeShaderIn == "vertex"){
					typeShader = glCreateShader(GL_VERTEX_SHADER);
					std::ifstream shaderStream(shaderFilePath, std::ios::in);
					if (shaderStream.is_open()){
						std::stringstream sstr;
						sstr << shaderStream.rdbuf();
						shaderSrc = sstr.str();
						shaderStream.close();
					}
				shaderSrcPtr = shaderSrc.c_str();
				glShaderSource(typeShader, 1, &shaderSrcPtr, NULL);
				glCompileShader(typeShader);
				glGetShaderiv(typeShader, GL_COMPILE_STATUS, &success);
				if (!success){
					glGetShaderInfoLog(typeShader, 512, NULL, infolog);
					std::cout << "Error vertexShader compile..." << infolog << std::endl;
				}
				}
				else if (typeShaderIn == "fragment"){
					typeShader = glCreateShader(GL_FRAGMENT_SHADER);
					std::ifstream shaderStream(shaderFilePath, std::ios::in);
					if (shaderStream.is_open()){
						std::stringstream sstr;
						sstr << shaderStream.rdbuf();
						shaderSrc = sstr.str();
						shaderStream.close();
					}
				shaderSrcPtr = shaderSrc.c_str();
				glShaderSource(typeShader, 1, &shaderSrcPtr, NULL);
				glCompileShader(typeShader);
				glGetShaderiv(typeShader, GL_COMPILE_STATUS, &success);
				if (!success){
					glGetShaderInfoLog(typeShader, 512, NULL, infolog);
					std::cout << "Error fragmentShader compile..." << infolog << std::endl;
				}
				}
			}
			//ShaderProgram(){}
			//deleteShader(){}
	};




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

	Shader vertexShader, fragmentShader;
	vertexShader.loadCompileShader("shaders/lessFive/vertexShaderRight.src", "vertex");
	fragmentShader.loadCompileShader("shaders/lessFive/fragmentShaderRight.src", "fragment");

	

	// Цикл рендеринга в окне
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;

}

