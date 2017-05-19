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
#include "Model.h"
#include "GameObject.h"

class Texture
{
public:
	Texture();
	~Texture();
	virtual void load(char* name);
	virtual void use();
	virtual void unload();
	FIBITMAP* image;
	FIBITMAP* image32Bit;
	unsigned int texID;
};

