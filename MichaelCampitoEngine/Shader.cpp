#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
Shader::Shader(std::string filev, std::string filef)
{
	filenamev = filev;
	filenamef = filef;
}


Shader::~Shader()
{
}

//Loads shaders
bool Shader::load() {
	cout << "load";
	bool work1 = compile(GL_VERTEX_SHADER);
	bool work2 = compile(GL_FRAGMENT_SHADER);
	if (work1 && work2) {
		GLint test;
		program=glCreateProgram();
		glAttachShader(program, vprogram);
		glAttachShader(program, fprogram);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &test);
		if (test == 0) {
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &test);
			GLchar* erArr = new GLchar[test];
			glGetProgramInfoLog(program, test, 0, erArr);
			glDeleteProgram(program);
			cout << erArr;
			delete[](erArr);
		}
		else {
			return true;
		}
	}
	else if (work1) {
		std::cout << work1;
	}
	else if (work2) {
		std::cout << work2;
	}
	program = 0;
	return false;
}

bool Shader::compile(GLenum shaderType) {
	GLint test;
	GLuint* whatShade;
	string* whatName;
	if (shaderType == GL_VERTEX_SHADER) {
		whatName = &filenamev;
		whatShade = &vprogram;
	}
	else {
		whatName = &filenamef;
		whatShade = &fprogram;
	}
	ifstream stream(*whatName, ios::binary);
	if (stream.is_open()) {
			stream.seekg(0, ios::end);
			int length = (int)stream.tellg();
			stream.seekg(0, ios::beg);

			char* fileContents = new char[length + 1];
			stream.read(fileContents, length);
			fileContents[length] = '\0';
			*whatShade = glCreateShader(shaderType);
			glShaderSource(*whatShade, 1, &fileContents, 0);
			glCompileShader(*whatShade);
			glGetShaderiv(*whatShade, GL_COMPILE_STATUS, &test);
			cout << fileContents;
			delete[](fileContents);
			if (test == 0) {
				glGetShaderiv(*whatShade, GL_INFO_LOG_LENGTH, &test);
				GLchar* erArr = new GLchar[test];
				glGetShaderInfoLog(*whatShade, test, 0, erArr);
				glDeleteShader(*whatShade);
				cout << erArr;
				delete[](erArr);
			}
			else {
				return true;
			}
		}
		else {
			cout << "There was a problem opening the file.";
		}
	return false;
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::unload() {
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);
	program = 0;
	vprogram = 0;
	fprogram = 0;
}
