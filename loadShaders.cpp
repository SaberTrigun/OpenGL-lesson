#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

void LoadShaders(const char * vertexFilePath, const char * fragmentFilePath, const char * fragmentFilePath2, unsigned int* shaderProgramOrangePtr, unsigned int* shaderProgramRedPtr){
	// Создаем шейдеры
	GLuint vertexShaderID		= glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderOrange	= glCreateShader(GL_FRAGMENT_SHADER);
	GLuint fragmentShaderRed	= glCreateShader(GL_FRAGMENT_SHADER);


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

	// Загружаем код Фрагментного шейдера из файла
	std::string fragmentShaderSrc2;
	std::ifstream fragmentShaderStream2(fragmentFilePath2, std::ios::in);
	if(fragmentShaderStream2.is_open()){
	    std::stringstream sstr;
	    sstr << fragmentShaderStream2.rdbuf();
	    fragmentShaderSrc2 = sstr.str();
	    fragmentShaderStream2.close();
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

	std::cout << "Compile fragment shader Orange..." << std::endl;
	char const * fragmentShaderSrcPtr = fragmentShaderSrc.c_str();
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSrcPtr, NULL);
	glCompileShader(fragmentShaderOrange);
	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "Error fragmentShader compile..." << infoLog << std::endl;
	}

	std::cout << "Compile fragment shader Red..." << std::endl;
	char const * fragmentShaderSrcPtr2 = fragmentShaderSrc2.c_str();
	glShaderSource(fragmentShaderRed, 1, &fragmentShaderSrcPtr2, NULL);
	glCompileShader(fragmentShaderRed);
	glGetShaderiv(fragmentShaderRed, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderRed, 512, NULL, infoLog);
		std::cout << "Error fragmentShader compile..." << infoLog << std::endl;
	}


	std::cout << "Compile shader program Orange..." << std::endl;
	unsigned int shaderProgramOrange = glCreateProgram();
	glAttachShader(shaderProgramOrange, vertexShaderID);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "Error shaderProgram compile..." << infoLog << std::endl;
	}

	std::cout << "Compile shader program Red..." << std::endl;
	unsigned int shaderProgramRed = glCreateProgram();
	glAttachShader(shaderProgramRed, vertexShaderID);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);
	glGetProgramiv(shaderProgramRed, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramRed, 512, NULL, infoLog);
		std::cout << "Error shaderProgram compile..." << infoLog << std::endl;
	}
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderRed);

	*shaderProgramOrangePtr= shaderProgramOrange;
	*shaderProgramRedPtr = shaderProgramRed;
}	
