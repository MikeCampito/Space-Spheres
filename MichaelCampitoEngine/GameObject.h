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
#include "Texture.h"
#include "transform.h"
class GameObject
{
public:
	GameObject();
	GameObject(vec3 loc, vec3 rot, vec3 size, float* t1, float* t2, float mass, float coltype);
	~GameObject();
	class Texture* customTex;
	class Model* customMod;
	void makeModel(char* name);
	void makeTexture(char* name);
	void render();
	void unload();
	void update();
	transform newtrans;
	bool collidesWith(GameObject* obB);
	enum ColType
	{
		COLLESS = 0,
		AABB = 1,
		SPHERE = 2
	};
	ColType type1;
};
