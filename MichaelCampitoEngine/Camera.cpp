#include "Camera.h"
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
using namespace glm;

Camera::Camera(){}

Camera::Camera(float* t1, float* t2, GLFWwindow* wind)
{
	newtrans = transform(vec3(0, 0, 7), vec3(0, 0, 0), vec3(1, 1, 1), 5, t1, t2);
	newtrans.rotMat = (mat3)yawPitchRoll(newtrans.rotation.y, newtrans.rotation.x, newtrans.rotation.z);
	//lightLoc = { 0, 2, 2 };
	zoom = 1.f;
	width = 800;
	height = 600;

	fovy = 3.14159f * .4f / zoom;
	aspect = (float)width / (float)height;
	zNear = .01f;
	zFar = 1000.f;
	newtrans.window = wind;
	glfwSetCursorPos(newtrans.window, 400, 300);
}


Camera::~Camera()
{
}

void Camera::camUpdate() {
	float sens = .002;
	int w = 800, h = 600;
	double x = 0, y = 0;
	glfwGetWindowSize(newtrans.window, &w, &h);
	glfwGetCursorPos(newtrans.window, &x, &y);
	newtrans.rotation.y -= sens * (x - w * .5f); //Yaw
	newtrans.rotation.x -= sens * (y - h * .5f); //Pitch

	//newtrans.rotation.x = glm::clamp(newtrans.rotation.z, (float)(-.5f * atan(1) * 4), (float)(.5f * atan(1) * 4));
	
	glfwSetCursorPos(newtrans.window, w*.5f, h*.5f);
	newtrans.rotMat = (mat3)glm::yawPitchRoll(newtrans.rotation.y, newtrans.rotation.x, newtrans.rotation.z);

	vec3 eye = newtrans.location;
	vec3 center = eye + newtrans.rotMat * vec3(0, 0, -1);
	vec3 up = newtrans.rotMat * vec3(0, 1, 0);

	lookAtMat = lookAt(eye, center, up);

	camMat = perspective(fovy, aspect, zNear, zFar) * lookAtMat;

	glUniformMatrix4fv(2, 1, GL_FALSE, &camMat[0][0]);
	glUniform3f(4, newtrans.location.x, newtrans.location.y, newtrans.location.z);
}