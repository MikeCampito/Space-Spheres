#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include "Shader.h"
#include <iostream>
#include "GLDebug.h"
#include "Camera.h"
#include <math.h>

class Model
{
public:
	Model();
	~Model();
	bool buffer(std::string objFile);
	void render();
private:
	unsigned int vertCount;
	GLuint vertArr;
};

