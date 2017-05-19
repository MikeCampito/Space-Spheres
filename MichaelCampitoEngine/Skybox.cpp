#include "Skybox.h"

Shader skyShader = Shader("shaders/svShader.glsl", "shaders/sfShader.glsl");

Skybox::Skybox(Camera* cam, Shader* shade)
{
	customMod = new Model();
	std::string s("models/box.obj");
	customMod->buffer(s);
	camRef = cam;
	shadeRef = shade;
	if(skyShader.load()==false){
		std::cout << "everything is stupid.";
	}
}


Skybox::~Skybox()
{
}

void Skybox::makeTexture() {
	customTex = new CubeMap();
	if (customTex->texID != 0) {
		std::cout << "We good boys";
	}
}

void Skybox::render() {
	glUseProgram(skyShader.program);
	glDisable(GL_CULL_FACE);
	customTex->use();
	vec3 camLocTemp = camRef->newtrans.location;
	camRef->newtrans.location = vec3(0, 0, 0);
	//camRef->camUpdate();
	vec3 eye = camRef->newtrans.location;
	vec3 center = eye + camRef->newtrans.rotMat * vec3(0, 0, -1);
	vec3 up = camRef->newtrans.rotMat * vec3(0, 1, 0);

	mat4 lookAtMat = glm::lookAt(eye, center, up);

	mat4 camMat = perspective(camRef->fovy, camRef->aspect, camRef->zNear, camRef->zFar) * lookAtMat;

	camRef->newtrans.location = camLocTemp;


	glUniformMatrix4fv(glGetUniformLocation(skyShader.program, "cameraMat"),1,GL_FALSE,&camMat[0][0]);
	glUniform3f(4, camRef->newtrans.location.x, camRef->newtrans.location.y, camRef->newtrans.location.z);
	glUniform1i(glGetUniformLocation(skyShader.program, "skybox"), 0);
	GameObject::render();
	glEnable(GL_CULL_FACE);
	glUseProgram(shadeRef->program);
	glClear(GL_DEPTH_BUFFER_BIT);
	
}