#pragma once
#include "Texture.h"
#include <vector>
class CubeMap :
	public Texture
{
public:
	CubeMap();
	~CubeMap();
	void use();
	void load(std::vector<const GLchar*> faceNames);
	std::vector<const GLchar*> faceNames;
};

