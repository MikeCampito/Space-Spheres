#include "CubeMap.h"



CubeMap::CubeMap()
{
	faceNames.push_back("textures/right2.jpg");
	faceNames.push_back("textures/left2.jpg");
	faceNames.push_back("textures/top2.jpg");
	faceNames.push_back("textures/bottom2.jpg");
	faceNames.push_back("textures/back2.jpg");
	faceNames.push_back("textures/front2.jpg");
	load(faceNames);
	std::cout << "we good?";
}


CubeMap::~CubeMap()
{
}

void CubeMap::load(std::vector<const GLchar*> faceNames) {
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	for (GLuint i = 0; i < faceNames.size(); i++) {
		image = FreeImage_Load(FreeImage_GetFileType(faceNames[i], 0), faceNames[i]);
		image32Bit = FreeImage_ConvertTo32Bits(image);
		FreeImage_FlipVertical(image32Bit);
		FreeImage_Unload(image);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_SRGB_ALPHA,
			FreeImage_GetWidth(image32Bit),
			FreeImage_GetHeight(image32Bit),
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			(void*)FreeImage_GetBits(image32Bit));
		FreeImage_Unload(image32Bit);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::use() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

}
