#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include <string.h>

class Shader
{
public:
	Shader(std::string filev, std::string filef);
	~Shader();
	GLuint program, vprogram, fprogram;

	std::string filenamev;
	std::string filenamef;

	//Loads shaders
	bool load();

	bool compile(GLenum shaderType);

	void use();

	void unload();
};

