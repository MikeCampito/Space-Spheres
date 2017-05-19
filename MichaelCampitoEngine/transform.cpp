#include "transform.h"
#include <iostream>

transform::transform()
{
}


transform::~transform()
{
}

transform::transform(vec3 loc, vec3 rot, vec3 si, float mas, float* t1, float* t2) {
	location = loc;
	rotation = rot;
	size = si;
	objwor = mat4();
	mass = mas;
	force = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);
	force = vec3(0, 0, 0);
	t = t1;
	window = glfwGetCurrentContext();
	dt = 0;
	t0 = t2;
	score = 0;
}

void transform::update() {
	float sens = .005;
	int w = 800, h = 600;
	double x = 0, y = 0;
	glfwGetWindowSize(window, &w, &h);
	glfwGetCursorPos(window, &x, &y);
	//rotation.y -= sens * (x - w * .5f); //Yaw
	//rotation.x -= sens * (y - h * .5f); //Pitch

	//rotation.x = clamp(rotation.z, (float)(-.5f * atan(1) * 4), (float)(.5f * atan(1) * 4));

	glfwSetCursorPos(window, w*.5f, h*.5f);
	//rotMat = (mat3)glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			force = vec3(-.4, 0, 0);
			velocity += rotMat * (force / mass);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			force = vec3(.4, 0, 0);
			velocity += rotMat * (force / mass);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			force = vec3(0, .4, 0);
			velocity += rotMat * (force / mass);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			force = vec3(0, -.4, 0);
			velocity += rotMat * (force / mass);
		}

		if (velocity != vec3()) {
			//velocity = normalize(velocity * speed);
		}
	if (location.y < -3) {
		velocity.y *= -1;
		location.y = -3;
		score++;
		
	}
	if (location.y > 3) {
		velocity.y *= -1;
		location.y = 3;
		score++;
	}

	if (location.x < -3.5) {
		velocity.x *= -1;
		location.x = -3.5;
		score++;
	}
	if (location.x > 3.5) {
		velocity.x *= -1;
		location.x = 3.5;
		score++;
	}
	dt = *t - *t0;
	location += (dt * velocity);
	speed1 = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
}

void transform::bounce(vec3 off, float speed2, float mass2) {
	float angle =  atan2((location.y - off.y), (location.x - off.x));

	velocity.x = cos(angle) * speed2 * mass2;
	velocity.x /= mass;
	
	velocity.y = sin(angle) * speed2 * mass2;
	velocity.y /= mass;
	
}