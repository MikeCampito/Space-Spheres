#pragma once
#include "GameObject.h"
#include "CubeMap.h"
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
#include "Texture.h"

class Skybox :
	public GameObject
{
public:
	Skybox(Camera* cam, Shader* shade);
	~Skybox();
	class Camera* camRef;
	class Shader* shadeRef;
	void render();
	void makeTexture();
};

