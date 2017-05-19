
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
#include "GameObject.h"
#include "Skybox.h"
#include <list>



int main()
{
	float score = 0;
	float t, t0;

	if (glfwInit() == GL_FALSE) {
		return -1;
	}

	// Initialize window
	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "MichaelCampito DSA1 Engine", NULL, NULL);
	if(GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}
	initDebug(); 

	//Model newModel = Model();
	//newModel.buffer("box.obj");

	
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	std::cout << "print";

	Shader newShader = Shader("shaders/vShader.glsl","shaders/fShader.glsl");
	if (newShader.load()) {
		
		newShader.use();
		std::cout << "\n" << newShader.program;
	}
	else {
		std::cin.ignore();
	}
	glfwSetTime(0);

	t = (float)glfwGetTime();
	t0 = t;
	glEnable(GL_DEPTH_TEST);
	Camera newCam = Camera(&t, &t0, GLFWwindowPtr);
	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	GameObject buildings[] = { GameObject(vec3(-5,0,0), vec3(0,1.5708,0), vec3(3,3.8,1), &t, &t0, 100, 0), GameObject(vec3(5,0,0), vec3(0,1.5708,0), vec3(3,3.8,1), &t, &t0, 100, 0), GameObject(vec3(0,-3.75,0), vec3(1.5708,1.5708,0), vec3(3,5,1), &t, &t0, 100, 0),  GameObject(vec3(0,3.75,0), vec3(1.5708,1.5708,0), vec3(3,5,1), &t, &t0, 100, 0) };
	buildings[0].makeTexture("textures/sci-fi_wall_texture1.jpg");
	buildings[0].makeModel("models/quad.obj");
	buildings[1].makeTexture("textures/sci-fi_wall_texture1.jpg");
	buildings[1].makeModel("models/quad.obj");
	buildings[2].makeTexture("textures/sci-fi_floor_texture2.jpg");
	buildings[2].makeModel("models/quad.obj");
	buildings[3].makeTexture("textures/sci-fi_floor_texture1.jpg");
	buildings[3].makeModel("models/quad.obj");

	GameObject gameOne[] = { GameObject(vec3(2,-1.4,0),vec3(0,0,0),vec3(.7,.7,.7), &t, &t0, 5, 2), GameObject(vec3(-1,1.5,0),vec3(0,0,0),vec3(.7,.7,.7), &t, &t0,5, 2), GameObject(vec3(3,2.6,0),vec3(0,0,0),vec3(.7,.7,.7), &t, &t0,3, 2), GameObject(vec3(-2, -2.8, 0), vec3(0,0,0), vec3(.7,.7,.7), &t, &t0, 4, 2), GameObject(vec3(-2.5,2.4,0),vec3(0,0,0),vec3(1,1,1), &t, &t0, 7, 2) };
	//Texture handling
	gameOne[0].makeTexture("textures/sci-fi_wall_texture1.jpg");
	gameOne[0].makeModel("models/sphere.obj");
	gameOne[1].makeTexture("textures/sci-fi_wall_texture1.jpg");
	gameOne[1].makeModel("models/sphere.obj");
	gameOne[2].makeTexture("textures/sci-fi_wall_texture1.jpg");
	gameOne[2].makeModel("models/sphere.obj");
	gameOne[3].makeTexture("textures/sci-fi_wall_texture1.jpg");
	gameOne[3].makeModel("models/sphere.obj");
	gameOne[4].makeTexture("textures/sphere-tex.jpg");
	gameOne[4].makeModel("models/sphere.obj");
	//Texture newTex;
	//newTex.load("TestTexture.png");
	Skybox newSkies = Skybox(&newCam, &newShader);
	newSkies.makeTexture();
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		float totalscore = 0;
		t0 = t;
		t = glfwGetTime();
		//Clear the canvas
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//Update physical simulation
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GLFWwindowPtr,1);
		}
		glUniform3f(3, 40, 5, 3);
		newSkies.render();
		
		//Draw buffered models
		newCam.camUpdate();
		//Render
		//newModel.render();
		//secModel.render();
		for (int i = 4; i >= 0; i--) {
			gameOne[i].update();
			if (i > 0) {
				for (int j = i - 1; j >= 0; j--) {
					if (gameOne[i].collidesWith(&gameOne[j])) {
						score-=1.2;
						float temp = gameOne[i].newtrans.speed1;
						gameOne[i].newtrans.bounce(gameOne[j].newtrans.location, gameOne[j].newtrans.speed1, gameOne[j].newtrans.mass);
						gameOne[j].newtrans.bounce(gameOne[i].newtrans.location, temp, gameOne[i].newtrans.mass);
					}
				}
			}
		}

		for (int i = 4; i >= 0; i--) {
			gameOne[i].newtrans.objwor = translate(gameOne[i].newtrans.location)*yawPitchRoll(gameOne[i].newtrans.rotation.y, gameOne[i].newtrans.rotation.x, gameOne[i].newtrans.rotation.z)*scale(gameOne[i].newtrans.size);
			glUniformMatrix4fv(8, 1, GL_FALSE, &gameOne[i].newtrans.objwor[0][0]);

			gameOne[i].render();
			if (i < 4) {
				buildings[i].newtrans.objwor = translate(buildings[i].newtrans.location)*yawPitchRoll(buildings[i].newtrans.rotation.y, buildings[i].newtrans.rotation.x, buildings[i].newtrans.rotation.z)*scale(buildings[i].newtrans.size);

				glUniformMatrix4fv(8, 1, GL_FALSE, &buildings[i].newtrans.objwor[0][0]);

				buildings[i].render();
			}
			totalscore += gameOne[i].newtrans.score;
		}
		totalscore += score;
		std::cout << totalscore << "\n\n";

		//Swap the front (what the screen displays) and back (what OpenGL draws to) buffers
		glfwSwapBuffers(GLFWwindowPtr);

		//Process input/window events
		//Process queued window, mouse, & keyboar callback events
		glfwPollEvents();
	}
	newShader.unload();
	//newTex.unload();
	for (int i = 3; i >= 0; i--) {
		gameOne[i].unload();
	}
	// Free GLFW memory.
	glfwTerminate();
	// End of Program.
	return 0;
}