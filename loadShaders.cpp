#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint LoadShaders(const char * vertexFilePath,const char * fragmentFilePath){
	// Создаем шейдеры
	GLuint vertexShaderID	= glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID	= glCreateShader(GL_FRAGMENT_SHADER);


	// Загружаем код Вершинного Шейдера из файла
	std::string vertexShaderSrc;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if(vertexShaderStream.is_open())
	{
	    std::stringstream sstr;
	    sstr << vertexShaderStream.rdbuf();
	    vertexShaderSrc= sstr.str();
	    vertexShaderStream.close();
	}

	// Загружаем код Фрагментного шейдера из файла
	std::string fragmentShaderSrc;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if(fragmentShaderStream.is_open()){
	    std::stringstream sstr;
	    sstr << fragmentShaderStream.rdbuf();
	    fragmentShaderSrc = sstr.str();
	    fragmentShaderStream.close();
	}

	int success;
	char infoLog[512];

	std::cout << "Compile vertex shader....." << std::endl;
	char const * vertexShaderSrcPtr = vertexShaderSrc.c_str();
	glShaderSource(vertexShaderID, 1, &vertexShaderSrcPtr, NULL);
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "Error vertexShader compile..." << infoLog << std::endl;
	}

	std::cout << "Compile fragment shader..." << std::endl;
	char const * fragmentShaderSrcPtr = fragmentShaderSrc.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSrcPtr, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << "Error fragmentShader compile..." << infoLog << std::endl;
	}

	std::cout << "Compile shader program..." << std::endl;
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmentShaderID);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error shaderProgram compile..." << infoLog << std::endl;
	}

	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderProgram;
}	
