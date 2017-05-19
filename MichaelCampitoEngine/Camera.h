#pragma once
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
#include <time.h>
#include "transform.h"
using namespace glm;

class Camera
{
public:
	Camera();
	Camera(float* t1, float* t2, GLFWwindow* wind);
	~Camera();
	void camUpdate();
	mat4x4 camMat;
	float t;
	vec3 lightLoc;
	mat3 rotMat;
	mat4 lookAtMat;
	transform newtrans;
	float zoom, fovy, aspect, zNear, zFar;
	int width, height;
	GLFWwindow* window;
};

