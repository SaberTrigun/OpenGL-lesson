#include "include/glad/glad.h"
#include "include/glm/glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum Shader_Type{VERTEX, FRAGMENT, GEOMETRIC};
class Shader{
	private:
		unsigned int 	typeShader, shaderProgram;
		std::string	shaderSrc;
		int 		success;
		char 		infolog [512];
		char const* 	shaderSrcPtr;
	public:
		void loadCompileShader(const char* shaderFilePath, Shader_Type typeShaderIn){
			if (typeShaderIn == VERTEX)
				typeShader = glCreateShader(GL_VERTEX_SHADER);
			else if (typeShaderIn == FRAGMENT)
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
				std::cout << "Error " << typeShaderIn << " compile..." << infolog << std::endl;
			}
			}
		
		void createProgram(Shader vertex, Shader fragment){
			shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertex.typeShader);
			glAttachShader(shaderProgram, fragment.typeShader);
			glLinkProgram(shaderProgram);
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success){
				glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
				std::cout << "Error shaderProgram compile..." << infolog << std::endl;
			}
		}
		void deleteShader(Shader vertex, Shader fragment){
			glDeleteShader(vertex.typeShader);
			glDeleteShader(fragment.typeShader);
		}
			
		void useProgram(){
			glUseProgram(shaderProgram);
		}
		void setInt(const std::string& name, const int value){
			glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
		}
						
		void setVec3(const std::string& name, const glm::vec3 &value){ 
			glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
		}
		void setVec3(const std::string& uniVar, float x, float y, float z){
			glUniform3f(glGetUniformLocation(shaderProgram, uniVar.c_str()), x, y, z);
		}
		void setVec4(const std::string& uniVar, float x, float y, float z, float w){
			glUniform4f(glGetUniformLocation(shaderProgram, uniVar.c_str()), x, y, z, w);
		}
		void setMat2(const std::string& uniVar, const glm::mat2 &mat){
			glUniformMatrix2fv(glGetUniformLocation(shaderProgram, uniVar.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void setMat3(const std::string& uniVar, const glm::mat3 &mat){
			glUniformMatrix2fv(glGetUniformLocation(shaderProgram, uniVar.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void setMat4(const std::string& uniVar, const glm::mat4 &mat){
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniVar.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void setFloat(const std::string& uniVar, const float fVar){
			glUniform1f(glGetUniformLocation(shaderProgram, uniVar.c_str()), fVar);
		}


};
