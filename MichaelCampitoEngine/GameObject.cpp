#include "GameObject.h"


GameObject::GameObject() {

}
GameObject::GameObject(vec3 loc, vec3 rot, vec3 size, float* t1, float* t2, float mas, float coltype)
{
	customMod = new Model();
	customTex = new Texture();
	newtrans = transform(loc, rot, size, mas, t1, t2);
	newtrans.velocity = vec3(0,0,0);
	newtrans.force = vec3(0, 0, 0);
	newtrans.rotMat = (mat3)yawPitchRoll(newtrans.rotation.y, newtrans.rotation.x, newtrans.rotation.z);
	if(coltype == 0){
		type1 = COLLESS;
	}
	else if (coltype == 1) {
		type1 = AABB;
	}
	else if (coltype == 2) {
		std::cout << "Why";
		type1 = SPHERE;
	}
}


GameObject::~GameObject()
{
	delete(customMod);
	delete(customTex);
}



void GameObject::unload() {
	customTex->unload();
}

void GameObject::makeModel(char* name) {
	std::string s(name);
	customMod->buffer(s);
}

void GameObject::makeTexture(char* name) {
	customTex->load(name);
}

void GameObject::render() {
	customTex->use();
	customMod->render();
}

void GameObject::update() {
	newtrans.update();
	newtrans.velocity.y -= (.8* newtrans.dt);
}

bool GameObject::collidesWith(GameObject* obB) {
	if (type1 == COLLESS || obB->type1 == COLLESS) {
		return false;
	}
	else if (type1 == AABB) {
		float xmin = newtrans.location.x - newtrans.size.x;
		float xmax = newtrans.location.x + newtrans.size.x;
		float ymin = newtrans.location.y - newtrans.size.y;
		float ymax = newtrans.location.y + newtrans.size.y;
		float zmin = newtrans.location.z - newtrans.size.z;
		float zmax = newtrans.location.z + newtrans.size.z;
		
		if (obB->type1 == AABB) {
			if (abs(newtrans.location.x - obB->newtrans.location.x) > newtrans.size.x + obB->newtrans.size.x) {
				return false;
			}
			else if (abs(newtrans.location.y - obB->newtrans.location.y) > newtrans.size.y + obB->newtrans.size.y) {
				return false;
			}
			else if (abs(newtrans.location.z - obB->newtrans.location.z) > newtrans.size.z + obB->newtrans.size.z) {
				return false;
			}
			else {
				return true;
			}
		}

		else {
			float distance = 0;

			if (xmin > obB->newtrans.location.x) {
				distance += pow((obB->newtrans.location.x - xmin), 2);
			}
			else if(xmax < obB->newtrans.location.x) {
				distance += pow((obB->newtrans.location.x - xmax),2);
			}
			if (ymin > obB->newtrans.location.y) {
				distance += pow((obB->newtrans.location.y - ymin), 2);
			}
			else if(ymax < obB->newtrans.location.y) {
				distance += pow((obB->newtrans.location.y - ymax), 2);
			}
			if (zmin > obB->newtrans.location.z) {
				distance += pow((obB->newtrans.location.z - zmin), 2);
			}
			else if (zmax < obB->newtrans.location.z) {
				distance += pow((obB->newtrans.location.z - zmax), 2);
			}
			if (distance > pow(obB->newtrans.size.x,2)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		float distance = 0;
		if (obB->type1 == SPHERE) {
			distance = (pow((newtrans.location.x - obB->newtrans.location.x), 2)
				+ pow((newtrans.location.y - obB->newtrans.location.y), 2)
				+ pow((newtrans.location.z - obB->newtrans.location.z), 2));
			if (distance > pow((newtrans.size.x + obB->newtrans.size.x),2)) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			float xmin = obB->newtrans.location.x - obB->newtrans.size.x ;
			float xmax = obB->newtrans.location.x + obB->newtrans.size.x ;
			float ymin = obB->newtrans.location.y - obB->newtrans.size.y ;
			float ymax = obB->newtrans.location.y + obB->newtrans.size.y ;
			float zmin = obB->newtrans.location.z - obB->newtrans.size.z ;
			float zmax = obB->newtrans.location.z + obB->newtrans.size.z ;
			if (xmin > newtrans.location.x) {
				distance += pow((newtrans.location.x - xmin), 2);
			}
			else if (xmax < newtrans.location.x) {
				distance += pow((newtrans.location.x - xmax), 2);
			}
			if (ymin > newtrans.location.y) {
				distance += pow((newtrans.location.y - ymin), 2);
			}
			else if (ymax < newtrans.location.y) {
				distance += pow((newtrans.location.y - ymax), 2);
			}
			if (zmin > newtrans.location.z) {
				distance += pow((newtrans.location.z - zmin), 2);
			}
			else if (zmax < newtrans.location.z) {
				distance += pow((newtrans.location.z - zmax), 2);
			}
			if (distance > pow(newtrans.size.x,2)) {
				return false;
			}
			else {
				return true;
			}
		}
	}

}