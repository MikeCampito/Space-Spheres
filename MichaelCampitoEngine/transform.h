#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
using namespace glm;

class transform
{
public:
	transform();
	~transform();
	
	GLFWwindow* window;
	vec3 location, rotation, size, velocity, force;
	mat3 rotMat;
	mat4 objwor;
	float* t;
	float dt;
	float* t0;
	float mass;
	float speed1;
	float score;
	transform(vec3 loc, vec3 rot, vec3 si, float mas, float* t1, float* t2);
	void bounce(vec3 off, float speed2, float mass2);
	void update();
};

